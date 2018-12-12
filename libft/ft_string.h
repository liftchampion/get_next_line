/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_string.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggerardy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/13 02:00:02 by ggerardy          #+#    #+#             */
/*   Updated: 2018/12/13 02:00:31 by ggerardy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_STRING_H
# define FT_STRING_H

# include <stdlib.h>
# include "libft.h"

typedef struct	s_string
{
	char		*data;
	size_t		len;
	size_t		capacity;
}				t_string;

void			ft_print_string(t_string *str);

void			ft_free_string(t_string **str);

t_int8			ft_string_fit(t_string **str);

t_int8			ft_string_push_back(t_string **str, char c);

t_string		*ft_make_string(size_t init_size);

#endif
