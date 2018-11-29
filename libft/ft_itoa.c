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

#include <stdlib.h>
#include "libft.h"

char		*ft_itoa(int n)
{
	int		sign;
	char	*res;
	int		tmp[10];
	int		i;
	int		j;

	sign = (n >= 0 ? 1 : -1);
	i = (n == 0 ? 1 : 0);
	j = 0;
	tmp[0] = 0;
	while (n != 0)
	{
		tmp[i] = n % 10 * sign;
		n /= 10;
		i++;
	}
	res = (char*)malloc(i + (sign == -1) + 1);
	if (!res)
		return (0);
	if (sign == -1)
		res[j++] = '-';
	while (i > 0)
		res[j++] = tmp[--i] + '0';
	res[j] = 0;
	return (res);
}
