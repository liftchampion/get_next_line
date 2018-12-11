#include "get_next_line.h"
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

#include "libft.h"


/*void ft_print_nonprintable(char *)
{

}*/


/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgalyeon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/11 09:04:05 by rgalyeon          #+#    #+#             */
/*   Updated: 2018/12/11 16:23:11 by rgalyeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "get_next_line.h"
#include <stdio.h>
#define WHITE "\x1B[0m"
#define RED "\x1B[31m"
#define GREEN "\x1B[32m"
#define BLUE "\x1B[34m"
#define YELLOW "\x1B[33m"

void	test01(void)
{
	int fd, fd2, fd3;
	int n;
	char *line;
	int file_size;

	/**************************************************************************/
	/*                                                                        */
	/*                           TEST_01_BIG_LINE                             */
	/*                                                                        */
	/**************************************************************************/
	system("mkdir -p tests");
	system("base64 < /dev/urandom | head -c 1000000 | tr -d '\n' | tr -d '\r'  > tests/01_test.txt");

	fd = open("tests/01_test.txt", O_RDONLY);
	fd2 = open("tests/01_test.txt.my", O_CREAT | O_RDWR | O_TRUNC, 0755);
	n = 0;
	while (get_next_line(fd, &line) == 1)
	{
		write(fd2, line, strlen(line));
		free(line);
		n++;
	}
	close(fd);
	close(fd2);

	system("diff tests/01_test.txt tests/01_test.txt.my > tests/01_test.txt.diff");
	fd3 = open("tests/01_test.txt.diff", O_RDONLY);
	file_size = read(fd3, NULL, 10);
	close (fd3);

	if (file_size == 0 && n == 1)
		printf("TEST_01_BIG_LINE" GREEN " [OK]\n" WHITE);
	else
	{
		if (n != 1)
		{
			printf("TEST_01_BIG_LINE" RED " [KO]\n" WHITE);
			printf(RED "Yours n - <%d>, ours - <%d>\n" WHITE, n, 1);
		}
		else
			printf("TEST_01_BIG_LINE" RED " DIFFS KO :(\n" WHITE);
	}
}

void	test02(void)
{
	int fd, fd2, fd3;
	int n;
	char *line;
	int file_size;

	/**************************************************************************/
	/*                                                                        */
	/*                           TEST_02_BIG_LINE                             */
	/*                                                                        */
	/**************************************************************************/

	system("mkdir -p tests");
	system("echo '\n\n'  > tests/02_test.txt");

	fd = open("tests/02_test.txt", O_RDONLY);
	fd2 = open("tests/02_test.txt.my", O_CREAT | O_RDWR | O_TRUNC, 0755);
	n = 0;
	while (get_next_line(fd, &line) == 1)
	{
		write(fd2, line, strlen(line));
		free(line);
		write(fd2, "\n", 1);
		n++;
	}
	close(fd);
	close(fd2);

	system("diff tests/02_test.txt tests/02_test.txt.my > tests/02_test.txt.diff");
	fd3 = open("tests/02_test.txt.diff", O_RDONLY);
	file_size = read(fd3, NULL, 10);
	close (fd3);

	if (file_size == 0 && n == 3)
		printf("TEST_02_LINE_BREAK" GREEN " [OK]\n" WHITE);
	else
	{
		if (n != 3)
		{
			printf("TEST_02_LINE_BREAK" RED " [KO]\n" WHITE);
			printf(RED "Yours n - <%d>, ours - <%d>\n" WHITE, n, 3);
		}
		else
			printf("TEST_02_LINE_BREAK" RED " DIFFS KO :(\n" WHITE);
	}
}

void	test03(void)
{
	int fd, fd2, fd3;
	int n;
	char *line;
	int file_size;

	/**************************************************************************/
	/*                                                                        */
	/*                         TEST_03_EMPTY_LINE                             */
	/*                                                                        */
	/**************************************************************************/

	system("mkdir -p tests");
	system(" > tests/03_test.txt");

	fd = open("tests/03_test.txt", O_RDONLY);
	fd2 = open("tests/03_test.txt.my", O_CREAT | O_RDWR | O_TRUNC, 0755);
	n = 0;
	while (get_next_line(fd, &line) == 1)
	{
		write(fd2, line, strlen(line));
		write(fd2, "\n", 1);
		n++;
	}
	close(fd);
	close(fd2);

	system("diff tests/03_test.txt tests/03_test.txt.my > tests/03_test.txt.diff");
	fd3 = open("tests/03_test.txt.diff", O_RDONLY);
	file_size = read(fd3, NULL, 10);
	close (fd3);

	if (file_size == 0 && n == 0)
		printf("TEST_03_EMPTY_FILE" GREEN " [OK]\n" WHITE);
	else
	{
		if (n != 0)
		{
			printf("TEST_03_EMPTY_FILE" RED " [KO]\n" WHITE);
			printf(RED "Yours n - <%d>, ours - <%d>\n" WHITE, n, 0);
		}
		else
			printf("TEST_03_EMPTY_FILE" RED " DIFFS KO :(\n" WHITE);
	}
}

void	test04(void)
{
	int fd, fd2, fd3;
	int n;
	char *line;
	int file_size;

	/**************************************************************************/
	/*                                                                        */
	/*                           TEST_04_ONE_LINE                             */
	/*                                                                        */
	/**************************************************************************/

	system("mkdir -p tests");
	system("echo 'Tests by rgalyeon! Have a nice day :)'  > tests/04_test.txt");

	fd = open("tests/04_test.txt", O_RDONLY);
	fd2 = open("tests/04_test.txt.my", O_CREAT | O_RDWR | O_TRUNC, 0755);
	n = 0;
	while (get_next_line(fd, &line) == 1)
	{
		write(fd2, line, strlen(line));
		free(line);
		write(fd2, "\n", 1);
		n++;
	}
	close(fd);
	close(fd2);

	system("diff tests/04_test.txt tests/04_test.txt.my > tests/04_test.txt.diff");
	fd3 = open("tests/04_test.txt.diff", O_RDONLY);
	file_size = read(fd3, NULL, 10);
	close (fd3);

	if (file_size == 0 && n == 1)
		printf("TEST_04_ONE_LINE" GREEN " [OK]\n" WHITE);
	else
	{
		if (n != 1)
		{
			printf("TEST_04_ONE_LINE" RED " [KO]\n" WHITE);
			printf(RED "Yours n - <%d>, ours - <%d>\n" WHITE, n, 1);
		}
		else
			printf("TEST_04_ONE_LINE" RED " DIFFS KO :(\n" WHITE);
	}
}

void	test05(void)
{
	int fd, fd2, fd3;
	int n;
	char *line;
	ssize_t file_size;

	/**************************************************************************/
	/*                                                                        */
	/*                           TEST_05_8_LINES                              */
	/*                                                                        */
	/**************************************************************************/

	system("mkdir -p tests");
	system("echo 'Hi'  > tests/05_test.txt");
	system("echo 'It is second line'  >> tests/05_test.txt");
	system("echo 'It'  >> tests/05_test.txt");
	system("echo 'is'  >> tests/05_test.txt");
	system("echo 'easy'  >> tests/05_test.txt");
	system("echo 'test'  >> tests/05_test.txt");
	system("echo 'for'  >> tests/05_test.txt");
	system("echo 'you :) Good luck!'  >> tests/05_test.txt");

	fd = open("tests/05_test.txt", O_RDONLY);
	fd2 = open("tests/05_test.txt.my", O_CREAT | O_RDWR | O_TRUNC, 0755);
	n = 0;
	while (get_next_line(fd, &line) == 1)
	{
		write(fd2, line, strlen(line));
		free(line);
		write(fd2, "\n", 1);
		n++;
	}
	close(fd);
	close(fd2);

	system("diff tests/05_test.txt tests/05_test.txt.my > tests/05_test.txt.diff");
	fd3 = open("tests/05_test.txt.diff", O_RDONLY);
	file_size = read(fd3, NULL, 10);
	close (fd3);

	if (file_size == 0 && n == 8)
		printf("TEST_05_8_LINES" GREEN " [OK]\n" WHITE);
	else
	{
		if (n != 8)
		{
			printf("TEST_05_8_LINE" RED " [KO]\n" WHITE);
			printf(RED "Yours n - <%d>, ours - <%d>\n" WHITE, n, 8);
		}
		else
			printf("TEST_05_8_LINE" RED " DIFFS [KO] :(\n" WHITE);
	}
}

void	test06(void)
{
	int fd, fd2, fd3;
	int n;
	char *line;
	ssize_t file_size;

	/**************************************************************************/
	/*                                                                        */
	/*                       TEST_06_by_vlegros                               */
	/*                                                                        */
	/**************************************************************************/

	system("mkdir -p tests");
	system("echo ''  > tests/06_test.txt");
	system("echo 'test test' | tr -d '\n'  >> tests/06_test.txt");

	fd = open("tests/06_test.txt", O_RDONLY);
	fd2 = open("tests/06_test.txt.my", O_CREAT | O_RDWR | O_TRUNC, 0755);
	n = 0;
	while (get_next_line(fd, &line) == 1)
	{
		write(fd2, line, strlen(line));
		if (n == 0)
			write(fd2, "\n", 1);
		free(line);
		n++;
	}
	close(fd);
	close(fd2);

	system("diff tests/06_test.txt tests/06_test.txt.my > tests/06_test.txt.diff");
	fd3 = open("tests/06_test.txt.diff", O_RDONLY);
	file_size = read(fd3, NULL, 10);
	close (fd3);

	if (file_size == 0 && n == 2)
		printf("TEST_06_by_vlegros" GREEN " [OK]\n" WHITE);
	else
	{
		if (n != 2)
		{
			printf("TEST_06_by_vlegros" RED " [KO]\n" WHITE);
			printf(RED "Yours n - <%d>, ours - <%d>\n" WHITE, n, 2);
		}
		else
			printf("TEST_06_by_vlegros" RED " DIFFS [KO] :(\n" WHITE);
	}
}


void	diman_tests()
{
	test01();
	test02();
	test03();
	test04();
	test05();
	test06();
}


int		main(void)
{
	char *line;
	int ret;
	//line = (char*)malloc(1000000);
	//for (int i = 0; i < 9; i++)
	//{
	//	line[i] = 'Z';
	//}
	//line[9] = 0;


	///diman_tests();
	///return (0);

	//int fd1 = open("asd", O_RDONLY);
	//int fd1 = open("../../BitBucket/libft_main/main.c", O_RDONLY);
	//int fd1 = open("main.o", O_RDONLY);
	//int fd1 = open("test_cat", O_RDONLY);
	//int fd1 = open("file1", O_RDONLY);
	int fd1 = open("1.txt", O_RDONLY);
	//int fd1 = open("one_big_fat_line.txt", O_RDONLY);
	//int fd1 = open("noenld", O_RDONLY);
	int fd2 = open("1.txt", O_RDONLY);
	int fd3 = open("empty_strs", O_RDONLY);

	ret = 2;
	int c = 0;
	/**while (ret && ret != -1)
	{
		//ret = get_next_line(fd2, &line);
		//printf("\n%d->%d: <%s>", fd2, ret, line);
		//ret = get_next_line(fd3, &line);
		//printf("\n%d->%d: <%s>", fd3, ret, line);

		//ft_putchar('<');
		ret = get_next_line(fd1, &line);
		if (ret == 0)
			break ;
		if (c != 0)
			printf("\n");

		///printf("{%p}\n", (void*)line);
		printf("%s", line);
		//ft_putstr(line);
		//ft_putchar('>');
		free(line);


		//printf("<%s>", line);
		//printf("\n%d->%d: <%s>", fd1, ret, line);
		c++;
	}*/



	int fd11 = open("file11", O_RDONLY);
	int fd12 = open("file12", O_RDONLY);
	int fd13 = open("file13", O_RDONLY);
	int fd14 = open("file14", O_RDONLY);
	int fd15 = open("file15", O_RDONLY);

	int fd21 = open("file21", O_RDONLY);
	int fd22 = open("file22", O_RDONLY);
	int fd23 = open("file23", O_RDONLY);
	int fd24 = open("file24", O_RDONLY);

	char *f1 = (char *)ft_memalloc(1000);
	char *f2 = (char *)ft_memalloc(1000);
	char *f3 = (char *)ft_memalloc(1000);
	char *f4 = (char *)ft_memalloc(1000);
	char *f5 = (char *)ft_memalloc(1000);

	char *f21 = (char *)ft_memalloc(1000);
	char *f22 = (char *)ft_memalloc(1000);
	char *f23 = (char *)ft_memalloc(1000);
	char *f24 = (char *)ft_memalloc(1000);

	int ret1 = 0;
	int ret2 = 0;
	int ret3 = 0;
	int ret4 = 0;
	int ret5 = 0;

	int ret21 = 0;
	int ret22 = 0;
	int ret23 = 0;
	int ret24 = 0;
	c = 0;
	ret = 1;
	while (ret > 0)
	{
		ret = 0;
		/*///printf("PASKUDA1\n");
		ret1 = get_next_line(fd11, &line);
		if (c != 0 && ret1 != 0)
			ft_strlcat(f1, "\n", 1000);
		if (ret1 != 0)
			ft_strlcat(f1, line, 1000);
		free(line);

		///printf("PASKUDA2\n");
		ret2 = get_next_line(fd12, &line);
		if (c != 0 && ret2 != 0)
			ft_strlcat(f2, "\n", 1000);
		if (ret2 != 0)
			ft_strlcat(f2, line, 1000);
		free(line);

		///printf("PASKUDA3\n");
		ret3 = get_next_line(fd13, &line);
		if (c != 0 && ret3 != 0)
			ft_strlcat(f3, "\n", 1000);
		if (ret3 != 0)
			ft_strlcat(f3, line, 1000);
		free(line);

		///printf("PASKUDA4\n");
		ret4 = get_next_line(fd14, &line);
		if (c != 0 && ret4 != 0)
			ft_strlcat(f4, "\n", 1000);
		if (ret4 != 0)
			ft_strlcat(f4, line, 1000);
		free(line);

		///printf("PASKUDA5\n");
		ret5 = get_next_line(fd15, &line);
		if (c != 0 && ret5 != 0)
			ft_strlcat(f5, "\n", 1000);
		if (ret5 != 0)
			ft_strlcat(f5, line, 1000);
		free(line);*/


		///printf("PASKUDA2.1\n");
		ret21 = get_next_line(fd21, &line);
		if (c != 0 && ret21 != 0)
			ft_strlcat(f21, "\n", 1000);
		if (ret21 != 0)
			ft_strlcat(f21, line, 1000);
		free(line);

		///printf("PASKUDA2.2\n");
		ret22 = get_next_line(fd22, &line);
		if (c != 0 && ret22 != 0)
			ft_strlcat(f22, "\n", 1000);
		if (ret22 != 0)
			ft_strlcat(f22, line, 1000);
		free(line);

		///printf("PASKUDA2.3\n");
		ret23 = get_next_line(fd23, &line);
		if (c != 0 && ret23 != 0)
			ft_strlcat(f23, "\n", 1000);
		if (ret23 != 0)
			ft_strlcat(f23, line, 1000);
		free(line);

		///printf("PASKUDA2.4\n");
		ret24 = get_next_line(fd24, &line);
		if (c != 0 && ret24 != 0)
			ft_strlcat(f24, "\n", 1000);
		if (ret24 != 0)
			ft_strlcat(f24, line, 1000);
		free(line);

		ret = ret1 + ret2 + ret3 + ret4 + ret5 + ret21 + ret22 + ret23 + ret24;

		c++;
	}
	///printf("%s%s%s%s%s\n", f1, f2, f3, f4, f5);
	//printf("%s\n%s\n%s\n%s\n", f21, f22, f23, f24);
	free(f1);
	free(f2);
	free(f3);
	free(f4);
	free(f5);

	free(f21);
	free(f22);
	free(f23);
	free(f24);




	return (0);
}

