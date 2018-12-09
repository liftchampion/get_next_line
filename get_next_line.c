#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include "libft.h"
#include "ft_debugger.h"

#include "get_next_line.h"


ssize_t ft_readn(const int fd, t_buf *buf)
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
}

t_result ft_get_line_from_buffer(t_buf *buf, char **line)
{
	ssize_t i;

	i = 0;
	while (buf->pos + i < buf->len && buf->buffer[buf->pos + i] != '\n')
		i++;
	*line = ft_strsub(buf->buffer, (unsigned int)buf->pos, (size_t)i);
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
	return (ENDL_NOT_FOUND);
}

t_result ft_append_line(t_buf *buf, int fd, char **line)
{
	char *new_part;
	char *tmp;
	t_result res;

	res = ENDL_NOT_FOUND;
	if ((size_t)buf->len != buf->capacity)
		return ENDL_GOT;
	while (res == ENDL_NOT_FOUND && (size_t)buf->len == buf->capacity)
	{
		ft_readn(fd, buf);
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
	static t_map *fd_buf = 0;
	t_buf **curr_buf;

	/**char b;
	if (fd == -1 || BUFF_SIZE <= 0 || read(fd, &b, 0) == -1)
		return (-1);*/
	if(fd_buf == 0)
		fd_buf = ft_make_custom_value_map(INT32_T, free);
	curr_buf = (t_buf**)ft_map_get(fd_buf, (void*)(size_t)fd);
	if (*(void**)curr_buf == fd_buf->nil)
	{
		if (!(*curr_buf = (t_buf*)malloc(sizeof(t_buf))))
			return (-1);
		**curr_buf = (t_buf){(char*)malloc(BUFF_SIZE), BUFF_SIZE, 0, 0};
		if (!(*curr_buf)->buffer || ft_readn(fd, *curr_buf) == -1)
			return (-1);
	}
	res = ft_get_line_from_buffer(*curr_buf, line);
	if (res == MALLOC_ERROR)
		return (0);
	if (res == ENDL_NOT_FOUND)
		res = ft_append_line(*curr_buf, fd, line);
	if (res == MALLOC_ERROR)
		return (0);
	if (res == ENDL_GOT || res == NO_LINE)
		return (res == ENDL_GOT ? 1 : 0);
	return (0);


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

