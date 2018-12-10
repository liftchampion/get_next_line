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

	i = 0;
	while (i < str->len)
	{
		ft_putchar(str->data[i]);
		i++;
	}
	//ft_putchar('\n');
}

t_v_string *ft_make_v_string(size_t init_size)
{
	t_v_string *str = (t_v_string*)malloc(sizeof(t_v_string) * 1);
	if (!str)
		return (0);
	str->capacity = init_size == 0 ? 1 : init_size;
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

t_int8 ft_v_string_push_back(t_v_string *str, char c)
{
	if (str->len == str->capacity - 1)
	{
		str->data = ft_realloc(str->data, str->capacity, str->capacity * 2);
		if (!str->data)
		{
			free(str);
			return (0);
		}
		str->capacity *= 2;
	}
	str->data[str->len++] = c;
	str->data[str->len] = 0;
	return (1);
}

void ft_v_string_free(t_v_string *str)
{
	if (!str)
		return ;
	free(str->data);
	free(str);
}

t_int8 ft_v_string_fit(t_v_string *str)
{
	if (str->len == str->capacity)
		return (1);
	str->data = ft_realloc(str->data, str->capacity, str->len);
	if (!str->data)
	{
		free(str);
		return (0);
	}
	str->capacity = str->len == 0 ? 1 : str->len;
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



t_result ft_get_line_from_buffer(t_buf *buf, t_v_string *str, int fd)
{
	//printf("PASKUDA\n");
	int was_endl;

	if (buf->pos >= buf->len)
	{
		buf->len = read(fd, buf->buffer, BUFF_SIZE);
		buf->pos = 0;
		//printf(YELLOW "%zu\n", buf->len);
		if (buf->len == 0)
			return (NO_LINE);
	}

	while (buf->pos < buf->len && buf->buffer[buf->pos] != '\n')
	{
		//printf("PIZDA\n");
		if (!ft_v_string_push_back(str, buf->buffer[buf->pos]))
			return (MALLOC_ERROR);
		buf->pos++;
	}
	was_endl = buf->buffer[buf->pos] == '\n' ? 1 : 0;
	buf->pos += was_endl;



	if (was_endl || (buf->pos - was_endl == buf->len && buf->len < buf->capacity))
		return (ENDL_GOT);

	return (ENDL_NOT_FOUND);
	//printf(GREEN "%d\n", i);


	//printf("PASKUDA2\n");
	/**if (buf->len == 0)
	{
		return (NO_LINE);
	}
	//printf("PASKUDA3\n");

	*line = ft_strsub(buf->buffer, (unsigned int)buf->pos, (size_t)i);  //TODO don't use strsub
	//printf(GREEN "<%s>\n", *line);
	if (!*line)
		return (MALLOC_ERROR);
	buf->pos += i;
	if (i == 0 && buf->pos == buf->len && (size_t)buf->len != buf->capacity)
	{
		return (NO_LINE);
	}
	if (buf->buffer[buf->pos] == '\n')
	{
		if (buf->pos != buf->len)
		{
			buf->pos++;
		}
		return (ENDL_GOT);
	}
	return (ENDL_NOT_FOUND);*/
}


t_result ft_append_line(t_buf *buf, int fd, t_v_string *str)
{
	t_result res;

	//printf("SUKA\n");
	res = ENDL_NOT_FOUND;
	/*if ((size_t)buf->len != buf->capacity)
		return ENDL_GOT;*/
	while (res == ENDL_NOT_FOUND)
	{
		//printf("PIDRILNIK\n");
		buf->len = read(fd, buf->buffer, BUFF_SIZE);
		buf->pos = 0;
		res = ft_get_line_from_buffer(buf, str, fd);
		if (res == MALLOC_ERROR || res == NO_LINE)
			return (res);
	}
	//printf(BLUE "<%s>\n", *line);
	//printf(WHITE);
	return (ENDL_GOT);
}

void ft_free_buf(void *buf)
{
	free(((t_buf*)buf)->buffer);
	free(buf);
}

int		get_next_line(const int fd, char **line)
{
	static t_map *fd_buf = 0;
	t_result res;
	t_buf **curr_buf;
	t_v_string *str;

	if (fd < 0)
		return (-1);

	if(fd_buf == 0)
		fd_buf = ft_make_custom_value_map(INT32_T, ft_free_buf);
	curr_buf = (t_buf**)ft_map_get(fd_buf, (void*)(size_t)fd);
	if (*(void**)curr_buf == fd_buf->nil)
	{
		if (!(*curr_buf = (t_buf*)malloc(sizeof(t_buf))))
			return (-1);
		**curr_buf = (t_buf){(char*)malloc(BUFF_SIZE), BUFF_SIZE, 0, 0};
		if (!(*curr_buf)->buffer || ((*curr_buf)->len = read(fd, (*curr_buf)->buffer, BUFF_SIZE)) == -1)
			return (-1);
	}

	//printf(RED "<%s> %zu %zu\n", (*curr_buf)->buffer, (*curr_buf)->len, (*curr_buf)->pos);
	//printf(WHITE);
	if ((*curr_buf)->len == 0)  //TODO move to get_line_from_buf use NO_LINE + ADD READ_ERROR
		return (0);
	str = ft_make_v_string(0);			// TODO do it only if needed
	res = ft_get_line_from_buffer(*curr_buf, str, fd);
	//printf(BLUE "<%s>%d\n", str->data, res);

	if (res == ENDL_NOT_FOUND)
		res = ft_append_line(*curr_buf, fd, str);
	if (res == MALLOC_ERROR)
		return (-1);
	//printf(GREEN "<%s>\n", str->data);
	//printf(WHITE);


	ft_v_string_fit(str);
	*line = str->data;
	free(str);


	if (res == NO_LINE)
	{
		ft_map_del(fd_buf, (void*)(size_t)fd);
		ft_free_map(&fd_buf);
		return (0);
	}

	/*if (res == ENDL_GOT || res == NO_LINE)
	{
		//return ((res == ENDL_GOT ? 1 : 0) * 666);
		return (res == ENDL_GOT ? 1 : 0);
	}*/
	//ft_print_v_string(str);

	return (1);  // TODO shrink to fit returned value


	/**i = -1;
	if (buffers[0].fd == JUST_INITIALIZED)
		while (++i < 11001)
			buffers[i] = (t_buf){i - 1, 0, BUFF_SIZE, BUFF_SIZE, BUFF_SIZE};*/

	/**if (buffers[fd + 1].buffer == 0)
	{
		if (!(buffers[fd + 1].buffer = (char*)malloc(buffers[fd + 1].capacity + 1)))
			return (0);
		buffers[fd + 1].fd = fd;
		(buffers[fd + 1].buffer)[buffers[fd + 1].capacity] = 0;
		ft_readn(fd, &buffers[fd + 1]);
	}*/



	/**printf("\n");
	res = ft_get_line_from_buffer(&buffers[fd + 1], line);
	if (res == MALLOC_ERROR)
		return (0);
	if (res == ENDL_NOT_FOUND)
		res = ft_append_line(&buffers[fd + 1], line);
	if (res == MALLOC_ERROR)
		return (0);
	if (res == ENDL_GOT || res == NO_LINE)
		return (res == ENDL_GOT ? 1 : 0);
	return (0);*/
}

