all:  get_next_line.c libft.a
	rm -f main
	clang -Wall -Wextra -c -g get_next_line.c ft_debugger.c main.c
	clang -Wall -Wextra -g main.o get_next_line.o ft_debugger.o libft.a -o main
	./main
valgrind: all
	valgrind --track-origins=yes --leak-check=full --show-leak-kinds=definite --errors-for-leak-kinds=definite ./main