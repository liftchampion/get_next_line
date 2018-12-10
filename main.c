#include "get_next_line.h"
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

#include "libft.h"


/*void ft_print_nonprintable(char *)
{

}*/

int		main(void)
{
	char *line;
	int ret;
	line = (char*)malloc(10);
	for (int i = 0; i < 9; i++)
	{
		line[i] = 'Z';
	}
	line[9] = 0;

	//int fd1 = open("asd", O_RDONLY);
	//int fd1 = open("../../BitBucket/libft_main/main.c", O_RDONLY);
	int fd1 = open("main.o", O_RDONLY);
	//int fd1 = open("test_cat", O_RDONLY);
	//int fd1 = open("file1", O_RDONLY);
	//int fd1 = open("1.txt", O_RDONLY);
	//int fd1 = open("noenld", O_RDONLY);
	int fd2 = open("1.txt", O_RDONLY);
	int fd3 = open("empty_strs", O_RDONLY);

	ret = 2;
	while (ret && ret != -1)
	{
		//ret = get_next_line(fd2, &line);
		//printf("\n%d->%d: <%s>", fd2, ret, line);
		//ret = get_next_line(fd3, &line);
		//printf("\n%d->%d: <%s>", fd3, ret, line);
		///if (ret != 2)
		///	printf("\n");
		ret = get_next_line(fd1, &line);
		///if (ret == 0)
		///	break ;
		//printf("<%s>", line);
		//printf("\n%d->%d: <%s>", fd1, ret, line);
	}

	/*FILE *f = fopen("test_cat", "w+");
	for (int e = 0; e < 256; e++)
	{
		fprintf(f, "%d = [%c] ", e, (char)e);
		if (e != 0 && e % 10 == 0)
			fprintf(f, "\n");
	}
	fclose(f);*/

	return (0);
}

