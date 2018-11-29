#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include "libft.h"

#define BUFF_SIZE 1

////////////////////////////////////////////////////////////////////////////////

#include <stdarg.h>

#define DEBUG_ON 0

#define RED "\x1B[31m"
#define GREEN "\x1B[32m"
#define YELLOW "\x1B[33m"
#define BLUE "\x1B[34m"
#define WHITE "\x1B[0m"
#define BOLD "\x1B[1m"

#define DEBUG(msg, ...) ft_debug(msg, (char*)__FILE__, (char*)__func__, __LINE__, ##__VA_ARGS__)

#define DEBUG_STREAM stdout

char **ft_get_vars_names(char *file, int line);

int ft_numlen(int num)
{
	int len;

	len = num >= 0 ? 0 : 1;
	while (num != 0)
	{
		num /= 10;
		len++;
	}
	return len;
}

void ft_print_char_debug(char c)
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
	fprintf(DEBUG_STREAM, BLUE);
	fflush(DEBUG_STREAM);
}

void ft_print_str_debug(char *str)
{
	fprintf(DEBUG_STREAM, BLUE "<");
	while (*str)
	{
		ft_print_char_debug(*str);
		str++;
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
		int j = (int)ft_strlen(func) + ft_numlen(line) + 2;
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

char** ft_get_vars_names(char *file, int line)
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
	ft_bzero(str, 150);
	int i = 0;
	while (read(fd, &b, 1) && b != '\n')
	{
		str[i] = b;
		i++;
	}
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

////////////////////////////////////////////////////////////////////////////////

typedef struct
{
	int		fd;
	char	*buffer;
	size_t	capacity;
	ssize_t	len;
	ssize_t	pos;
}			t_buf;

typedef enum {
	MALLOC_ERROR,
	NO_LINE,
	ENDL_NOT_FOUND,
	ENDL_GOT
} t_result;


ssize_t ft_readn(const int fd, t_buf *buf)
{
	ssize_t res_of_read;

	res_of_read = read(fd, buf->buffer, buf->capacity);
	buf->len = res_of_read;
	buf->pos = 0;
	while (buf->len != buf->capacity)
	{
		res_of_read = read(fd, buf->buffer + buf->len, buf->capacity - buf->len);
		buf->len += res_of_read;
		if (res_of_read == 0)
		{
			break ;
		}
	}
	return buf->len;
}

t_result ft_get_line_from_buffer(t_buf *buf, char **line)
{
	ssize_t i;

	i = 0;
	DEBUG("%d", buf->pos);
	while (buf->pos + i < buf->len && buf->buffer[buf->pos + i] != '\n')
		i++;
	*line = ft_strsub(buf->buffer, (unsigned int)buf->pos, (size_t)i);
	if (!*line)
		return (MALLOC_ERROR);
	buf->pos += i;
	DEBUG("new part is %s", *line);
	DEBUG("%d %d", buf->pos, i);
	if (buf->buffer[buf->pos] == '\n')
	{
		if (buf->pos != buf->len)
		{
			buf->pos++;
		}
		DEBUG("%d", buf->pos);
		DEBUG("ENDL_GOT %s", buf->buffer);
		return (ENDL_GOT);
	}
	if (i == 0)
	{
		DEBUG("NO_LINE");
		return (NO_LINE);
	}
	DEBUG("ENDL_NOT_FOUND %s", buf->buffer);
	return (ENDL_NOT_FOUND);
}

t_result ft_append_line(t_buf *buf, char **line)
{
	char *new_part;
	char *tmp;
	t_result res;

	DEBUG("called");
	res = ENDL_NOT_FOUND;
	if (buf->len != buf->capacity)
		return ENDL_GOT;
	while (res == ENDL_NOT_FOUND && buf->len == buf->capacity)
	{
		ft_readn(buf->fd, buf);
		res = ft_get_line_from_buffer(buf, &new_part);
		if (res == MALLOC_ERROR)
			return (MALLOC_ERROR);
		tmp = ft_strjoin(*line, new_part);
		if (tmp == 0)
		{
			free(new_part);
			return (MALLOC_ERROR);
		}
		free(*line);
		*line = tmp;
	}
	return (ENDL_GOT);
}

int		get_next_line(const int fd, char **line)
{
	t_result res;

	static t_buf buf = (t_buf){-1, 0, BUFF_SIZE, BUFF_SIZE, BUFF_SIZE};
	if (buf.buffer == 0)
	{
		DEBUG("mallocing buffer");
		if (!(buf.buffer = (char*)malloc(buf.capacity + 1)))
			return (0);
		buf.fd = fd;
		(buf.buffer)[buf.capacity] = 0;
		ft_readn(fd, &buf);
	}
	printf("\n");
	DEBUG("FIRST CALL: %d %s %d %d %d\n", buf.fd, buf.buffer, buf.capacity, buf.len, buf.pos);
	res = ft_get_line_from_buffer(&buf, line);
	if (res == MALLOC_ERROR)
		return (0);
	if (res == ENDL_NOT_FOUND)
		res = ft_append_line(&buf, line);
	DEBUG("total line is %s", *line);
	if (res == MALLOC_ERROR)
		return (0);
	if (res == ENDL_GOT || res == NO_LINE)
		return (res == ENDL_GOT ? 1 : 0);
	return (0);
}

int		main(void)
{
	char *line;
	int ret;
	line = (char*)malloc(10);
	for (int i = 0; i < 9; i++)
	{
		line[i] = 'A';
	}
	line[9] = 0;
	int fd = open("file1", O_RDONLY);

	ret = 1;
	while (ret)
	{
		ret = get_next_line(fd, &line);
		printf("\n%d: <%s>", ret, line);
	}

	return (0);
}