all: main.c libft.a
	rm -f main
	gcc -c main.c
	gcc main.o libft.a -o main
	./main