/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shapka                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggerardy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/26 17:25:22 by ggerardy          #+#    #+#             */
/*   Updated: 2018/12/13 02:05:38 by ggerardy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "ft_string.h"

void			ft_print_string(t_string *str)
{
	size_t i;

	if (!str)
	{
		ft_putstr("NO V_STRING\n");
		return ;
	}
	i = 0;
	while (i < str->len)
	{
		ft_putchar(str->data[i]);
		i++;
	}
	ft_putchar('\n');
}

t_string		*ft_make_string(size_t init_size)
{
	t_string *str;

	str = (t_string*)malloc(sizeof(t_string) * 1);
	if (!str)
		return (0);
	str->capacity = init_size <= 1 ? 2 : init_size;
	str->data = (char*)malloc(sizeof(char) * (str->capacity));
	if (!str->data)
	{
		free(str);
		return (0);
	}
	str->data[0] = '\0';
	str->len = 0;
	return (str);
}

void			ft_free_string(t_string **str)
{
	if (!str || !*str)
		return ;
	free((*str)->data);
	free(*str);
	*str = 0;
}

t_int8			ft_string_push_back(t_string **str_ptr, char c)
{
	t_string *str;

	if (!str_ptr || !*str_ptr)
		return (-1);
	str = *str_ptr;
	if (str->len == str->capacity - 1)
	{
		str->data = ft_realloc(str->data, str->capacity, str->capacity * 2);
		if (!str->data)
		{
			ft_free_string(str_ptr);
			return (0);
		}
		str->capacity *= 2;
	}
	str->data[str->len++] = c;
	str->data[str->len] = 0;
	return (1);
}

t_int8			ft_string_fit(t_string **str_ptr)
{
	t_string *str;

	if (!str_ptr || !*str_ptr)
		return (-1);
	str = *str_ptr;
	if (str->len == str->capacity - 1)
		return (1);
	str->data = ft_realloc(str->data, str->capacity,
			str->len == 0 ? 2 : str->len + 1);
	if (!str->data)
	{
		ft_free_string(str_ptr);
		return (0);
	}
	str->data[str->len] = 0;
	str->capacity = str->len == 0 ? 2 : str->len + 1;
	return (1);
}
