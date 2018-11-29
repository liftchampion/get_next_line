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

#ifndef FT_DEBUGGER_H
# define FT_DEBUGGER_H

# define DEBUG_ON 1

# define PRINT_INDEXES 1

# define RED "\x1B[1m\x1B[31m"
# define GREEN "\x1B[1m\x1B[32m"
# define YELLOW "\x1B[1m\x1B[33m"
# define BLUE "\x1B[1m\x1B[34m"
# define WHITE "\x1B[0m"
# define BOLD "\x1B[1m"
# define GREY "\x1B[0m\x1B[37m"

# define DEBUG(msg, ...) ft_debug(msg, (char*)__FILE__, (char*)__func__, __LINE__, ##__VA_ARGS__)

# define DEBUG_STREAM stdout

void ft_debug(char *msg, char* file, char *func, int line, ...);

#endif
