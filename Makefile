all:  get_next_line.c libft.a
	rm -f main
	clang -Wall -Wextra -c get_next_line.c ft_debugger.c main.c
	clang -Wall -Wextra main.o get_next_line.o ft_debugger.o libft.a -o main
	./main
valgrind: all
	~/.brew/bin/valgrind --track-origins=yes --leak-check=full --show-leak-kinds=definite --errors-for-leak-kinds=definite ./main

final: libft/Makefile
	make -C libft/ fclean && make -C libft/
	clang -Wall -Wextra -Werror -I libft/includes -o get_next_line.o -c get_next_line.c
	clang -Wall -Wextra -Werror -I libft/includes -o main.o -c main.c
	clang -o test_gnl main.o get_next_line.o -I libft/includes -L libft/ -lft