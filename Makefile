all:  get_next_line.c libft.a
	rm -f main
	clang -Wall -Wextra -c get_next_line.c ft_debugger.c
	clang -Wall -Wextra get_next_line.o ft_debugger.o libft.a -o main
	./main