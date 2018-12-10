#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# define BUFF_SIZE 30000000

#include<string.h>
#include<unistd.h>
#include "libft.h"

typedef struct
{
	char	*buffer;
	ssize_t	capacity;
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

typedef struct	s_v_string
{
	char		*data;
	size_t		capacity;
	size_t		len;
}				t_v_string;

int		get_next_line(const int fd, char **line);




void *ft_realloc(void *old_data, size_t prev_size, size_t new_size);

void ft_v_string_free(t_v_string *str);

t_int8 ft_v_string_fit(t_v_string *str);

t_int8 ft_v_string_push_back(t_v_string *str, char c);

t_v_string *ft_make_v_string(size_t init_size);

#endif
