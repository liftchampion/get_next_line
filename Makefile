all:  get_next_line.c libft.a
	rm -f main
	clang -Wall -Wextra -c get_next_line.c ft_debugger.c main.c
	clang -Wall -Wextra main.o get_next_line.o ft_debugger.o libft.a -o main
	./main