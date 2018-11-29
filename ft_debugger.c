/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shapka.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggerardy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/26 17:25:22 by ggerardy          #+#    #+#             */
/*   Updated: 2018/11/26 17:25:22 by ggerardy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>
#include <stdio.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include "ft_debugger.h"

static char **ft_get_vars_names(char *file, int line);

static void        ft_free_matrix(void **ptr, size_t n)
{
	size_t i;

	i = 0;
	if (!ptr)
	{
		return ;
	}
	while (i < n && ptr[i])
	{
		free(ptr[i]);
		i++;
	}
	free(ptr);
}

static int     ft_is_in_charset(char c, char const *charset)
{
	while (*charset)
	{
		if (*charset == c)
			return (1);
		charset++;
	}
	return (0);
}

static unsigned int ft_count_words(char const *str, char const *charset)
{
	int c;
	int was_space;

	c = 0;
	was_space = 1;
	while (*str && ft_is_in_charset(*str, charset))
	{
		str++;
	}
	while (*str)
	{
		if (!ft_is_in_charset(*str, charset) && was_space)
			c++;
		was_space = ft_is_in_charset(*str, charset);
		str++;
	}
	return (c);
}

static unsigned int ft_strlen_delim(char const *str, int delim_by_spaces,
									char const *charset)
{
	unsigned int len;

	len = 0;
	while (*str && (!delim_by_spaces || !ft_is_in_charset(*str, charset)))
	{
		len++;
		str++;
	}
	return (len);
}

static unsigned int ft_strlcpy_delim(char *dest, char const *src,
									 unsigned int size, char const *c)
{
	unsigned int i;

	i = 0;
	while (src[i] != '\0' && i < size - 1 && !ft_is_in_charset(*src, c))
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (ft_strlen_delim(src, 0, c));
}

static int          ft_initializator(char ***strs, int count_words,
									 int *was_space, unsigned int *i)
{
	*was_space = 1;
	*i = 0;
	*strs = (char**)malloc(sizeof(char*) * count_words + 1);
	if (!*strs)
		return (0);
	strs[0][0] = 0;
	return (1);
}

char                **ft_split_charset(char const *str, char const *c)
{
	char            **strs;
	int             was_space;
	unsigned int    i;

	if (!ft_initializator(&strs, ft_count_words(str, c), &was_space, &i))
		return (0);
	while (*str)
	{
		if (was_space && !ft_is_in_charset(*str, c))
		{
			strs[i] = (char*)malloc(sizeof(char) *
									ft_strlen_delim(str, 1, c) + 1);
			strs[i + 1] = 0;
			if (!strs[i])
			{
				ft_free_matrix((void**)strs, -1);
				return (0);
			}
			ft_strlcpy_delim(strs[i++], str, ft_strlen_delim(str, 1, c) + 1, c);
		}
		was_space = ft_is_in_charset(*str, c);
		str++;
	}
	return (strs);
}

static char				*m_ft_itoa(int n)
{
	int				sign;
	char			*res;
	int				tmp[10];
	int				i;
	int				j;

	sign = (n >= 0 ? 1 : -1);
	i = (n == 0 ? 1 : 0);
	j = 0;
	tmp[0] = 0;
	while (n != 0)
	{
		tmp[i] = n % 10 * sign;
		n /= 10;
		i++;
	}
	res = (char*)malloc(i + (sign == -1) + 1);
	if (!res)
		return (0);
	if (sign == -1)
		res[j++] = '-';
	while (i > 0)
		res[j++] = tmp[--i] + '0';
	res[j] = 0;
	return (res);
}


static int m_ft_numlen(int num)
{
	int len;

	len = num > 0 ? 0 : 1;
	while (num != 0)
	{
		num /= 10;
		len++;
	}
	return len;
}

static void ft_print_char_debug(char c)
{
	if ((c >= 0 && c <= 31) || c == 127)
	{
		if (c == '\n')
			fprintf(DEBUG_STREAM, YELLOW "\\n");
		else
			fprintf(DEBUG_STREAM, YELLOW "\\%d", c);
	}
	else
	{
		fprintf(DEBUG_STREAM, BLUE "%c", c);
	}
	fflush(DEBUG_STREAM);
}

static void ft_print_index_superscript(int n, char pows[10][4])
{
	char *num = m_ft_itoa(n);
	int i = 0;
	while (num[i])
	{
		fprintf(DEBUG_STREAM, GREY "%s", pows[num[i] - '0']);
		i++;
	}
	free(num);
}

static void ft_print_str_debug(char *str)
{
	int i = 0;
	char pows[10][4] = {
			"\xe2\x81\xb0\0",
			"\xc2\xb9\0\0",
			"\xc2\xb2\0\0",
			"\xc2\xb3\0\0",
			"\xe2\x81\xb4\0",
			"\xe2\x81\xb5\0",
			"\xe2\x81\xb6\0",
			"\xe2\x81\xb7\0",
			"\xe2\x81\xb8\0",
			"\xe2\x81\xb9\0",
	};

	fprintf(DEBUG_STREAM, BLUE "<");
	while (str[i])
	{
		ft_print_char_debug(str[i]);
		if (PRINT_INDEXES)
		{
			ft_print_index_superscript(i, pows);
		}
		fprintf(DEBUG_STREAM, BLUE);
		i++;
	}
	fprintf(DEBUG_STREAM, BLUE ">");
}

void ft_debug(char *msg, char* file, char *func, int line, ...)
{
	if (DEBUG_ON)
	{
		int i = 0;
		char **vars = ft_get_vars_names(file, line);
		if (vars == 0)
		{
			printf(RED "\nNE ZAMOLOCHILOS'!!!\n");
			fflush(stdout);
			printf(WHITE);
			return ;
		}
		va_list args;
		va_start(args, line);
		fprintf(DEBUG_STREAM, RED "\n%s:%d: ", func, line);
		int j = (int)strlen(func) + m_ft_numlen(line) + 2;
		while (j++ < 30)
			fprintf(DEBUG_STREAM, " ");
		fflush(DEBUG_STREAM);
		while (*msg) {
			if (*msg != '%') {
				fprintf(DEBUG_STREAM, GREEN "%c", *msg);
				fflush(DEBUG_STREAM);
				fprintf(DEBUG_STREAM, WHITE);
				msg++;
			} else {
				fprintf(DEBUG_STREAM, BLUE);
				fflush(DEBUG_STREAM);
				fprintf(DEBUG_STREAM, BLUE "%s=", vars[i++]);
				fflush(DEBUG_STREAM);
				msg++;
				if (*msg == 0)
					break;
				if (*msg == 's')
					ft_print_str_debug(va_arg(args, char*));
				else if (*msg == 'd')
					fprintf(DEBUG_STREAM, "%i", va_arg(args, int));
				else if (*msg == 'c')
					ft_print_char_debug(va_arg(args, int));
				else if (*msg == 'p')
					fprintf(DEBUG_STREAM, "%p", va_arg(args, void*));
				fflush(DEBUG_STREAM);
				msg++;
				fprintf(DEBUG_STREAM, RED);
			}
		}
		va_end(args);
		fprintf(DEBUG_STREAM, WHITE);
		fflush(DEBUG_STREAM);
	}
}

static char** ft_get_vars_names(char *file, int line)
{
	int fd = open(file, O_RDONLY);
	int current_line = 1;
	char b;
	while (read(fd, &b, 1) && current_line != line)
	{
		if (b == '\n')
		{
			current_line++;
		}
	}
	char buf[150];
	char *str = (char*)buf;
	bzero(str, 150);
	int i = 0;
	while (read(fd, &b, 1) && b != '\n')
	{
		str[i] = b;
		i++;
	}
	close(fd);
	i = 0;
	while (i < 2){
		while (*str && *str != '"')
			str++;
		str++;
		i++;
	}
	char **vars = ft_split_charset(str, " ,\t();");
	if (vars == 0)
	{
		printf(RED "\nNE ZAMOLOCHILOS'!!!\n");
		fflush(stdout);
		printf(WHITE);
		return 0;
	}
	return vars;
}