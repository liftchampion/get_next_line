#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# define BUFF_SIZE 1

# define INIT_VECT_SIZE 0

#include<string.h>
#include<unistd.h>
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

typedef struct	s_v_string
{
	char		*data;
	size_t		len;
	size_t		capacity;
}				t_v_string;

int		get_next_line(const int fd, char **line);




void *ft_realloc(void *old_data, size_t prev_size, size_t new_size);

void ft_print_v_string(t_v_string *str);

void ft_v_string_free(t_v_string **str);

t_int8 ft_v_string_fit(t_v_string **str);

t_int8 ft_v_string_push_back(t_v_string **str, char c);

t_v_string *ft_make_v_string(size_t init_size);

#endif
