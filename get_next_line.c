#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include "libft.h"
#include "ft_debugger.h"

#include "get_next_line.h"


void ft_print_v_string(t_v_string *str)
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
	ft_putchar('\n'); // TODO verni, suka
}

t_v_string *ft_make_v_string(size_t init_size)
{
	t_v_string *str = (t_v_string*)malloc(sizeof(t_v_string) * 1);
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

void *ft_realloc(void *old_data, size_t prev_size, size_t new_size)
{
	void *new_data;
	size_t i;

	if (!old_data)
		return (0);
	new_data = ft_memalloc(new_size);
	if (!new_data)
	{
		free(old_data);
		return (0);
	}
	i = 0;
	while (i < prev_size && i < new_size)
	{
		((char*)new_data)[i] = ((char*)old_data)[i];
		++i;
	}
	free(old_data);
	return (new_data);
}

void ft_v_string_free(t_v_string **str)
{
	if (!str || !*str)
		return ;
	free((*str)->data);
	free(*str);
	*str = 0;
}

t_int8 ft_v_string_push_back(t_v_string **str_ptr, char c)
{
	t_v_string *str;

	if (!str_ptr || !*str_ptr)
		return (-1);
	str = *str_ptr;
	if (str->len == str->capacity - 1)
	{
		str->data = ft_realloc(str->data, str->capacity, str->capacity * 2);
		if (!str->data)
		{
			ft_v_string_free(str_ptr);
			return (0);
		}
		str->capacity *= 2;
	}
	str->data[str->len++] = c;
	str->data[str->len] = 0;
	return (1);
}


t_int8 ft_v_string_fit(t_v_string **str_ptr)
{
	t_v_string *str;

	if (!str_ptr || !*str_ptr)
		return (-1);
	str = *str_ptr;
	if (str->len == str->capacity - 1)
		return (1);
	str->data = ft_realloc(str->data, str->capacity, //(size_t)-1);   //TODO test -1
										str->len == 0 ? 2 : str->len + 1);
	if (!str->data)
	{
		ft_v_string_free(str_ptr);
		return (0);
	}
	str->data[str->len] = 0;
	str->capacity = str->len == 0 ? 2 : str->len + 1;
	return (1);
}




/**ssize_t ft_readn(const int fd, t_buf *buf)
{
	ssize_t res_of_read;

	res_of_read = read(fd, buf->buffer, buf->capacity);
	if (res_of_read == -1)
		return (-1);
	buf->len = res_of_read;
	buf->pos = 0;
	while ((size_t)buf->len != buf->capacity)
	{
		res_of_read = read(fd, buf->buffer + buf->len, buf->capacity - buf->len);
		if (res_of_read == -1)
			return (-1);
		buf->len += res_of_read;
		if (res_of_read == 0)
			break ;
	}
	return buf->len;
}*/



t_result ft_get_line_from_buffer(t_buf *buf, t_v_string **str, int fd)
{
	int was_endl;

	if (buf->pos >= buf->len && buf->len == buf->capacity)
	{
		buf->len = read(fd, buf->buffer, BUFF_SIZE);
		buf->pos = 0;
		if (buf->len <= 0)
			return (buf->len == 0 ? NO_LINE : ERROR);
	}
	else if (buf->pos >= buf->len)
		return (*str == 0 ? NO_LINE : ENDL_GOT);
	if (!*str)
		if (!(*str = ft_make_v_string(INIT_VECT_SIZE)))
			return (ERROR);
	while (buf->pos < buf->len && buf->buffer[buf->pos] != '\n')
	{
		if (!ft_v_string_push_back(str, buf->buffer[buf->pos]))
			return (ERROR);
		buf->pos++;
	}
	was_endl = (buf->pos < buf->len && buf->buffer[buf->pos] == '\n') ? 1 : 0;
	buf->pos += was_endl;
	if (was_endl || (buf->pos - was_endl == buf->len && buf->len < buf->capacity))
		return (ENDL_GOT);
	return (ENDL_NOT_FOUND);
}


t_result ft_append_line(t_buf *buf, int fd, t_v_string *str)
{
	t_result res;

	//if (res != ENDL_NOT_FOUND) // TODO na krainyak
	//	return (res);
	res = ENDL_NOT_FOUND;
	while (res == ENDL_NOT_FOUND)
	{
		buf->len = read(fd, buf->buffer, BUFF_SIZE);
		buf->pos = 0;
		res = ft_get_line_from_buffer(buf, &str, fd);
		if (res == ERROR || res == NO_LINE)
			return (res);
	}
	return (ENDL_GOT);
}

void ft_free_buf(void *buf)
{
	free(((t_buf*)buf)->buffer);
	free(buf);
}

t_result ft_gnl_init_works(int fd, t_map **fd_bf, t_buf ***curr_buf)
{
	t_result res;

	res = fd < 0 ? ERROR : ENDL_NOT_FOUND;
	if (res == ERROR)
		return (res);
	if (!*fd_bf)
		*fd_bf = ft_make_custom_value_map(INT32_T, ft_free_buf);
	if (!*fd_bf)
		return (ERROR);
	*curr_buf = (t_buf**)ft_map_get(*fd_bf, (void*)(size_t)fd);
	if (!*curr_buf)
		return (ERROR);
	if (**(void***)curr_buf == (*fd_bf)->nil)
	{
		if (!(**curr_buf = (t_buf*)malloc(sizeof(t_buf))))
			return (ERROR);
		***curr_buf = (t_buf){(char*)malloc(BUFF_SIZE), 0, 0, BUFF_SIZE};
		if (!(**curr_buf)->buffer || ((**curr_buf)->len = read(fd,
				(**curr_buf)->buffer, BUFF_SIZE)) == -1)
			return (ERROR);
	}
	return (res);
}

int		get_next_line(const int fd, char **line)
{
	static t_map *fd_bf = 0;
	t_result res;
	t_buf **curr_buf;
	t_v_string *str;

	str = 0;
	curr_buf = 0;
	res = !line ? ERROR : ft_gnl_init_works(fd, &fd_bf, &curr_buf);
	if (res != ERROR)
		res = ft_get_line_from_buffer(*curr_buf, &str, fd);
	if (res == ENDL_NOT_FOUND)
		res = ft_append_line(*curr_buf, fd, str);
	if (res == ERROR || !ft_v_string_fit(&str))
		res = ERROR;
	if (res != ERROR)
		*line = str == 0 ? 0 : str->data;
	else
		*line = 0;
	free(str);
	if (res == NO_LINE || res == ERROR)
	{
		ft_map_del(fd_bf, (void*)(size_t)fd);
		if (fd_bf && fd_bf->size == 0)
			ft_free_map(&fd_bf);
		return (res);							// TODO be sure about errors
	}
	return (1);
}

