# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ggerardy <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/10/29 22:33:54 by ggerardy          #+#    #+#              #
#    Updated: 2018/12/13 01:58:26 by ggerardy         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a
SRCS = $(wildcard *.c) $(wildcard ft_map/*.c) $(wildcard ft_string/*.c)
OBJS = $(SRCS:.c=.o)
HEADERS = libft.h
FLAGS = -Wall -Wextra -Werror

.PHONY: all clean fclean re

all: $(NAME)

$(NAME): $(OBJS) $(HEADERS)
	ar rcs $(NAME) $(OBJS)
	ranlib $(NAME)

build: $(SRCS) $(HEADERS)
	gcc $(FLAGS) -c $(SRCS)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all
