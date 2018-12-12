/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shapka                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggerardy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/26 17:25:22 by ggerardy          #+#    #+#             */
/*   Updated: 2018/11/29 16:09:36 by ggerardy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# define BUFF_SIZE 1

# define INIT_VECT_SIZE 16

# include <string.h>
# include "libft.h"

typedef struct	s_buf
{
	char	*buffer;
	ssize_t	pos;
	ssize_t	len;
	ssize_t	capac;
}				t_buf;

typedef enum {
	ERROR = -1,
	NO_LINE = 0,
	ENDL_GOT = 1,
	ENDL_NOT_FOUND = 2,
}	t_result;

int				get_next_line(const int fd, char **line);

#endif
