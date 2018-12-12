#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# define BUFF_SIZE 1

# define INIT_VECT_SIZE 0

#include <string.h>
#include <unistd.h>
#include "libft.h"

typedef struct
{
	char	*buffer;
	ssize_t	pos;
	ssize_t	len;
	ssize_t	capacity;
}			t_buf;

typedef enum {
	ERROR = -1,
	NO_LINE = 0,
	ENDL_GOT = 1,
	ENDL_NOT_FOUND = 2,
} t_result;

int		get_next_line(const int fd, char **line);

#endif
