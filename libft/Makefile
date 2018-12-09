# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ggerardy <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/10/29 22:33:54 by ggerardy          #+#    #+#              #
#    Updated: 2018/12/09 04:57:19 by ggerardy         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a
SRCS = ./ft_map/ft_char_cmp_funcs.c ./ft_map/ft_get_cmp_func.c ./ft_map/ft_get_free_func.c ./ft_map/ft_map.h ./ft_map/ft_map_works.c ./ft_map/ft_s_int_cmp_funcs.c ./ft_map/ft_types.h ./ft_map/ft_u_int_cmp_funcs.c ./ft_map/libft.h ./ft_map/rb_tree_assists.c ./ft_map/rb_tree_delete.c ./ft_map/rb_tree_delete_assist.c ./ft_map/rb_tree_insert.c ./ft_map/rb_tree_insert_assist.c ./ft_map/rb_tree_merge.c \
./ft_atoi.c ./ft_bzero.c ./ft_free_matrix.c ./ft_is_in_charset.c ./ft_isalnum.c ./ft_isalpha.c ./ft_isascii.c ./ft_isdigit.c ./ft_isprint.c ./ft_isspace.c ./ft_itoa.c ./ft_lstadd.c ./ft_lstdel.c ./ft_lstdelone.c ./ft_lstiter.c ./ft_lstmap.c ./ft_lstnew.c ./ft_memalloc.c ./ft_memccpy.c ./ft_memchr.c ./ft_memcmp.c ./ft_memcpy.c ./ft_memdel.c ./ft_memmove.c ./ft_memset.c ./ft_pow.c ./ft_print_words_table.c ./ft_putchar.c ./ft_putchar_fd.c ./ft_putchar_u_fd.c ./ft_putendl.c ./ft_putendl_fd.c ./ft_putnbr.c ./ft_putnbr_fd.c ./ft_putstr.c ./ft_putstr_fd.c ./ft_putstr_u.c ./ft_putstr_u_fd.c ./ft_split_charset.c ./ft_strcat.c ./ft_strchr.c ./ft_strclr.c ./ft_strcmp.c ./ft_strcpy.c ./ft_strdel.c ./ft_strdup.c ./ft_strequ.c ./ft_striter.c ./ft_striteri.c ./ft_strjoin.c ./ft_strlcat.c ./ft_strlcpy.c ./ft_strlen.c ./ft_strmap.c ./ft_strmapi.c ./ft_strncat.c ./ft_strncmp.c ./ft_strncpy.c ./ft_strnequ.c ./ft_strnew.c ./ft_strnstr.c ./ft_strrchr.c ./ft_strrev.c ./ft_strsplit.c ./ft_strstr.c ./ft_strsub.c ./ft_strtrim.c ./ft_tolower.c ./ft_toupper.c ./ft_strset.c
OBJS = ./ft_map/ft_char_cmp_funcs.o ./ft_map/ft_get_cmp_func.o ./ft_map/ft_get_free_func.o ./ft_map/ft_map_works.o ./ft_map/ft_s_int_cmp_funcs.o ./ft_map/ft_u_int_cmp_funcs.o ./ft_map/rb_tree_assists.o ./ft_map/rb_tree_delete.o ./ft_map/rb_tree_delete_assist.o ./ft_map/rb_tree_insert.o ./ft_map/rb_tree_insert_assist.o ./ft_map/rb_tree_merge.o \
./ft_atoi.o ./ft_bzero.o ./ft_free_matrix.o ./ft_is_in_charset.o ./ft_isalnum.o ./ft_isalpha.o ./ft_isascii.o ./ft_isdigit.o ./ft_isprint.o ./ft_isspace.o ./ft_itoa.o ./ft_lstadd.o ./ft_lstdel.o ./ft_lstdelone.o ./ft_lstiter.o ./ft_lstmap.o ./ft_lstnew.o ./ft_memalloc.o ./ft_memccpy.o ./ft_memchr.o ./ft_memcmp.o ./ft_memcpy.o ./ft_memdel.o ./ft_memmove.o ./ft_memset.o ./ft_pow.o ./ft_print_words_table.o ./ft_putchar.o ./ft_putchar_fd.o ./ft_putchar_u_fd.o ./ft_putendl.o ./ft_putendl_fd.o ./ft_putnbr.o ./ft_putnbr_fd.o ./ft_putstr.o ./ft_putstr_fd.o ./ft_putstr_u.o ./ft_putstr_u_fd.o ./ft_split_charset.o ./ft_strcat.o ./ft_strchr.o ./ft_strclr.o ./ft_strcmp.o ./ft_strcpy.o ./ft_strdel.o ./ft_strdup.o ./ft_strequ.o ./ft_striter.o ./ft_striteri.o ./ft_strjoin.o ./ft_strlcat.o ./ft_strlcpy.o ./ft_strlen.o ./ft_strmap.o ./ft_strmapi.o ./ft_strncat.o ./ft_strncmp.o ./ft_strncpy.o ./ft_strnequ.o ./ft_strnew.o ./ft_strnstr.o ./ft_strrchr.o ./ft_strrev.o ./ft_strsplit.o ./ft_strstr.o ./ft_strsub.o ./ft_strtrim.o ./ft_tolower.o ./ft_toupper.o ./ft_strset.o
HEADERS = libft.h
FLAGS = -Wall -Wextra -Werror

.PHONY: all clean fclean re

all: $(NAME)

$(NAME): $(OBJS) $(HEADERS)
	ar rcs  $(NAME) $(OBJS)
	ranlib $(NAME)

build: $(SRCS) $(HEADERS)
	gcc $(FLAGS) -c $(SRCS)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all
