#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# define BUFF_SIZE 50

#include<string.h>
#include<unistd.h>

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
	ENDL_GOT,
	JUST_INITIALIZED = -777
} t_result;

int		get_next_line(const int fd, char **line);

#endif
