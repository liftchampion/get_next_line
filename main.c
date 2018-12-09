#include "get_next_line.h"
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

#include "libft.h"

int		main(void)
{

	t_map *map = ft_make_std_map(INT32_T, INT32_T);


	char *line;
	int ret;
	line = (char*)malloc(10);
	for (int i = 0; i < 9; i++)
	{
		line[i] = 'A';
	}
	line[9] = 0;

	int fd1 = open("asd", O_RDONLY);
	//int fd1 = open("../../BitBucket/libft_main/main.c", O_RDONLY);
	//int fd1 = open("file1", O_RDONLY);
	int fd2 = open("1.txt", O_RDONLY);
	int fd3 = open("empty_strs", O_RDONLY);

	ret = 2;
	while (ret)
	{
		//ret = get_next_line(fd2, &line);
		//printf("\n%d->%d: <%s>", fd2, ret, line);
		//ret = get_next_line(fd3, &line);
		//printf("\n%d->%d: <%s>", fd3, ret, line);
		if (ret != 2)
			printf("\n");
		ret = get_next_line(fd1, &line);
		if (ret == 0)
			break ;
		printf("<%s> %d", line, ret);
		//printf("\n%d->%d: <%s>", fd1, ret, line);
	}

	return (0);
}

