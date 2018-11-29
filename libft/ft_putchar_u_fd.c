/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shapka.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggerardy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/26 17:25:22 by ggerardy          #+#    #+#             */
/*   Updated: 2018/11/26 17:25:22 by ggerardy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "libft.h"

static char		*ft_int_to_unicode(int n, char *bytes)
{
	if (n < ft_pow(2, 7))
		bytes[0] = (char)n;
	else if (n < ft_pow(2, 11))
	{
		bytes[0] = 192 + n / 64;
		bytes[1] = 128 + n % 64;
	}
	else if (n < ft_pow(2, 16))
	{
		bytes[0] = 224 + n / 4096;
		bytes[1] = 128 + (n / 64) % 64;
		bytes[2] = 128 + (n % 64);
	}
	else
	{
		bytes[0] = 240 + n / 262144;
		bytes[1] = 128 + (n / 4096) % 64;
		bytes[2] = 128 + (n / 64) % 64;
		bytes[3] = 128 + n % 64;
	}
	return (bytes);
}

void			ft_putchar_u_fd(int c, int fd)
{
	char uni_char[5];

	ft_bzero(uni_char, 5);
	if (c >= 0 && c <= ft_pow(2, 21) - 1)
	{
		ft_int_to_unicode(c, uni_char);
	}
	else
	{
		uni_char[0] = (char)c;
	}
	write(fd, uni_char, ft_strlen(uni_char));
}
