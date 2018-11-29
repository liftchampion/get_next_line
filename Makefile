all: main.c libft.a
	rm -f main
	clang -c main.c
	clang main.o libft.a -o main
	./main