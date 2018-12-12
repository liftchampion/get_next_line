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
	{
		remove("tests/01_test.txt");
		remove("tests/01_test.txt.my");
		remove("tests/01_test.txt.diff");
		printf("TEST_01_BIG_LINE" GREEN " [OK]\n" WHITE);
	}
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
	/*                          TEST_02_LINE_BREAKS                           */
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
	{
		remove("tests/02_test.txt");
		remove("tests/02_test.txt.my");
		remove("tests/02_test.txt.diff");
		printf("TEST_02_LINE_BREAK" GREEN " [OK]\n" WHITE);
	}
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
	{
		remove("tests/03_test.txt");
		remove("tests/03_test.txt.my");
		remove("tests/03_test.txt.diff");
		printf("TEST_03_EMPTY_FILE" GREEN " [OK]\n" WHITE);
	}
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
	{
		remove("tests/04_test.txt");
		remove("tests/04_test.txt.my");
		remove("tests/04_test.txt.diff");
		printf("TEST_04_ONE_LINE" GREEN " [OK]\n" WHITE);
	}
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
	{
		remove("tests/05_test.txt");
		remove("tests/05_test.txt.my");
		remove("tests/05_test.txt.diff");
		printf("TEST_05_8_LINES" GREEN " [OK]\n" WHITE);
	}
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
	{
		remove("tests/06_test.txt");
		remove("tests/06_test.txt.my");
		remove("tests/06_test.txt.diff");
		printf("TEST_06_by_vlegros" GREEN " [OK]\n" WHITE);
	}
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


void	test07(void)
{
	int fd;
	int out;
	int p[2];
	char *line;
	int n = 0;

	/**************************************************************************/
	/*                                                                        */
	/*                       TEST_07_FOUR_LINES                               */
	/*                                                                        */
	/**************************************************************************/

	fd = 1;
	out = dup(fd);
	pipe(p);

	dup2(p[1], fd);
	write(fd, "lol\nkek\nbek\nmek\n", 16);
	dup2(out, fd);
	close(p[1]);
	get_next_line(p[0], &line);
	if (strcmp(line, "lol") == 0)
		n++;
	free(line);
	get_next_line(p[0], &line);
	if (strcmp(line, "kek") == 0)
		n++;
	free(line);
	get_next_line(p[0], &line);
	if (strcmp(line, "bek") == 0)
		n++;
	free(line);
	get_next_line(p[0], &line);
	if (strcmp(line, "mek") == 0)
		n++;
	free(line);
	if (get_next_line(p[0], &line) == 0)
	{
		if (n == 4)
			printf("TEST_07_FOUR_LINES" GREEN " [OK]\n" WHITE);
	}
	else
	if (n != 4)
	{
		printf("TEST_07_FOUR_LINES" RED " [KO]\n" WHITE);
		printf(RED "Yours n - <%d>, ours - <%d>\n" WHITE, n, 4);
	}
	else
		printf("TEST_07_FOUR_LINES" RED " DIFFS [KO] :(\n" WHITE);
}


void	test08(void)
{
	int fd;
	int out;
	int p[2];
	char *line;
	int n = 0;

	/**************************************************************************/
	/*                                                                        */
	/*                            TEST_08_STDIN                               */
	/*                                                                        */
	/**************************************************************************/

	fd = 1;
	out = dup(fd);
	pipe(p);

	dup2(p[1], fd);
	write(fd, "lolkekcheburek", 14);
	dup2(out, fd);
	close(p[1]);
	get_next_line(p[0], &line);
	if (strcmp(line, "lolkekcheburek") == 0)
		n++;
	free(line);
	if (get_next_line(p[0], &line) == 0)
	{
		if (n == 1)
			printf("TEST_08_STDIN" GREEN " [OK]\n" WHITE);
	}
	else
	if (n != 1)
	{
		printf("TEST_08_STDIN" RED " [KO]\n" WHITE);
		printf(RED "Yours n - <%d>, ours - <%d>\n" WHITE, n, 1);
	}
	else
		printf("TEST_08_STDIN" RED " DIFFS [KO] :(\n" WHITE);
}

void	test09(void)
{
	int fd, fd2, fd3;
	int n;
	char *line;
	ssize_t file_size;

	/**************************************************************************/
	/*                                                                        */
	/*                       TEST_09_ZERO_BYTES                               */
	/*                                                                        */
	/**************************************************************************/


	system("mkdir -p tests");
	system(" > tests/09_test.txt");
	system("dd if=/dev/zero of=tests/09_test.txt bs=100 count=5 &> /dev/null");

	fd = open("tests/09_test.txt", O_RDONLY);
	fd2 = open("tests/09_test.txt.my", O_CREAT | O_RDWR | O_TRUNC, 0755);
	n = 0;
	while (get_next_line(fd, &line) == 1)
	{
		write(fd2, line, 500);
		free(line);
		n++;
	}
	close(fd);
	close(fd2);

	system("diff tests/09_test.txt tests/09_test.txt.my > tests/09_test.txt.diff");
	fd3 = open("tests/09_test.txt.diff", O_RDONLY);
	file_size = read(fd3, NULL, 10);
	close (fd3);

	if (file_size == 0 && n == 1)
	{
		remove("tests/09_test.txt");
		remove("tests/09_test.txt.my");
		remove("tests/09_test.txt.diff");
		printf("TEST_09_ZERO_BYTES" GREEN " [OK]\n" WHITE);
	}
	else
	{
		if (n != 0)
		{
			printf("TEST_09_ZERO_BYTES" RED " [KO]\n" WHITE);
			printf(RED "Yours n - <%d>, ours - <%d>\n" WHITE, n, 0);
		}
		else
			printf("TEST_09_~ERO_BYTES" RED " DIFFS [KO] :(\n" WHITE);
	}
}


void	test10(void)
{
	int fd;
	int n;
	char *line;

	/**************************************************************************/
	/*                                                                        */
	/*                           TEST_10_BAD_FD                               */
	/*                                                                        */
	/**************************************************************************/

	system("mkdir -p tests");

	fd = -1;
	n = 0;

	if (get_next_line(fd, &line) == -1 && n == 0)
		printf("TEST_10_BAD_FD" GREEN " [OK]\n" WHITE);
	else
	{
		if (n != 0)
		{
			printf("TEST_10_BAD_FD" RED " [KO]\n" WHITE);
			printf(RED "Yours n - <%d>, ours - <%d>\n" WHITE, n, 0);
		}
		else
			printf("TEST_10_BAD_FD" RED " DIFFS [KO] :(\n" WHITE);
	}
}


void	test11(void)
{
	int fd, fd2;
	char *line;

	/**************************************************************************/
	/*                                                                        */
	/*                           TEST_11_MUL_FD                               */
	/*                                                                        */
	/**************************************************************************/

	system("mkdir -p tests");
	system("echo 'lol\ncheburek' > tests/11_test.txt");
	system("echo 'kek' > tests/11_test1.txt");

	fd = open("tests/11_test.txt", O_RDONLY);
	fd2 = open("tests/11_test1.txt", O_RDONLY);

	get_next_line(fd, &line);
	if (strcmp(line, "lol") == 0)
	{
		free(line);
		get_next_line(fd2, &line);
		if (strcmp(line, "kek") == 0)
		{
			free(line);
			get_next_line(fd, &line);
			if (strcmp(line, "cheburek") == 0)
			{
				free(line);
				remove("tests/11_test.txt");
				remove("tests/11_test1.txt");
				printf("TEST_11_MUL_FD" GREEN " [OK]\n" WHITE);
				return ;
			}
		}
	}
	printf("TEST_11_MUL_FD" RED " DIFFS [KO] :(\n" WHITE);
}

void	test12(void)
{
	/**************************************************************************/
	/*                                                                        */
	/*                           TEST_12_MUL_FD                               */
	/*                                                                        */
	/**************************************************************************/

	printf("TEST_12_MUL_FD ");

	char *line = 0;
	int k = 6;
	while (k < 50)
	{
		get_next_line(k, &line);
		k++;
	}

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

	char *f1_ref = (char *)ft_memalloc(1000);
	char *f2_ref = (char *)ft_memalloc(1000);
	char *f3_ref = (char *)ft_memalloc(1000);
	char *f4_ref = (char *)ft_memalloc(1000);
	char *f5_ref = (char *)ft_memalloc(1000);

	char *f21_ref = (char *)ft_memalloc(1000);
	char *f22_ref = (char *)ft_memalloc(1000);
	char *f23_ref = (char *)ft_memalloc(1000);
	char *f24_ref = (char *)ft_memalloc(1000);

	int ret1 = 0;
	int ret11 = 0;
	int ret2 = 0;
	int ret3 = 0;
	int ret4 = 0;
	int ret5 = 0;

	int ret21 = 0;
	int ret22 = 0;
	int ret23 = 0;
	int ret24 = 0;

	int c = 0;
	int ret = 1;


	while (ret > 0)
	{
		ret = 0;
		///printf("PASKUDA1\n");
		ret1 = get_next_line(fd11, &line);
		if (c != 0 && ret1 > 0)
			ft_strlcat(f1, "\n", 1000);
		if (ret1 > 0)
			ft_strlcat(f1, line, 1000);
		free(line);

		///printf("PASKUDA11\n");
		ret11 = get_next_line(fd11, &line);
		if (ret11 > 0)
			ft_strlcat(f1, "\n", 1000);
		if (ret11 > 0)
			ft_strlcat(f1, line, 1000);
		free(line);

		///printf("PASKUDA2\n");
		ret2 = get_next_line(fd12, &line);
		if (c != 0 && ret2 > 0)
			ft_strlcat(f2, "\n", 1000);
		if (ret2 > 0)
			ft_strlcat(f2, line, 1000);
		free(line);

		///printf("PASKUDA3\n");
		ret3 = get_next_line(fd13, &line);
		if (c != 0 && ret3 > 0)
			ft_strlcat(f3, "\n", 1000);
		if (ret3 > 0)
			ft_strlcat(f3, line, 1000);
		free(line);

		///printf("PASKUDA4\n");
		ret4 = get_next_line(fd14, &line);
		if (c != 0 && ret4 > 0)
			ft_strlcat(f4, "\n", 1000);
		if (ret4 > 0)
			ft_strlcat(f4, line, 1000);
		free(line);

		///printf("PASKUDA5\n");
		ret5 = get_next_line(fd15, &line);
		if (c != 0 && ret5 > 0)
			ft_strlcat(f5, "\n", 1000);
		if (ret5 > 0)
			ft_strlcat(f5, line, 1000);
		free(line);


		///printf("PASKUDA2.1\n");
		ret21 = get_next_line(fd21, &line);
		if (c != 0 && ret21 > 0)
			ft_strlcat(f21, "\n", 1000);
		if (ret21 > 0)
			ft_strlcat(f21, line, 1000);
		free(line);

		///printf("PASKUDA2.2\n");
		ret22 = get_next_line(fd22, &line);
		if (c != 0 && ret22 > 0)
			ft_strlcat(f22, "\n", 1000);
		if (ret22 > 0)
			ft_strlcat(f22, line, 1000);
		free(line);

		///printf("PASKUDA2.3\n");
		ret23 = get_next_line(fd23, &line);
		if (c != 0 && ret23 > 0)
			ft_strlcat(f23, "\n", 1000);
		if (ret23 > 0)
			ft_strlcat(f23, line, 1000);
		free(line);

		///printf("PASKUDA2.4\n");
		ret24 = get_next_line(fd24, &line);
		if (c != 0 && ret24 > 0)
			ft_strlcat(f24, "\n", 1000);
		if (ret24 > 0)
			ft_strlcat(f24, line, 1000);
		free(line);

		ret = ret1 + ret11 + ret2 + ret3 + ret4 + ret5 + ret21 + ret22 + ret23 + ret24;

		c++;
	}
	//printf("%s%s%s%s%s\n\n", f1, f2, f3, f4, f5);
	//printf("%s\n%s\n%s\n%s\n", f21, f22, f23, f24);
	//printf("%s", f1);


	close(fd11);
	close(fd12);
	close(fd13);
	close(fd14);
	close(fd15);

	close(fd21);
	close(fd22);
	close(fd23);
	close(fd24);

	fd11 = open("file11", O_RDONLY);
	fd12 = open("file12", O_RDONLY);
	fd13 = open("file13", O_RDONLY);
	fd14 = open("file14", O_RDONLY);
	fd15 = open("file15", O_RDONLY);

	fd21 = open("file21", O_RDONLY);
	fd22 = open("file22", O_RDONLY);
	fd23 = open("file23", O_RDONLY);
	fd24 = open("file24", O_RDONLY);


	read(fd11, f1_ref, 1000);
	read(fd12, f2_ref, 1000);
	read(fd13, f3_ref, 1000);
	read(fd14, f4_ref, 1000);
	read(fd15, f5_ref, 1000);

	read(fd21, f21_ref, 1000);
	read(fd22, f22_ref, 1000);
	read(fd23, f23_ref, 1000);
	read(fd24, f24_ref, 1000);


	int err_count = 0;

	if (strcmp(f1, f1_ref) != (-1 * '\n') && strcmp(f1, f1_ref) != 0)
		err_count++;
	if (strcmp(f2, f2_ref) != (-1 * '\n') && strcmp(f2, f2_ref) != 0)
		err_count++;
	if (strcmp(f3, f3_ref) != (-1 * '\n') && strcmp(f3, f3_ref) != 0)
		err_count++;
	if (strcmp(f4, f4_ref) != (-1 * '\n') && strcmp(f4, f4_ref) != 0)
		err_count++;
	if (strcmp(f5, f5_ref) != (-1 * '\n') && strcmp(f5, f5_ref) != 0)
		err_count++;
	if (strcmp(f21, f21_ref) != (-1 * '\n') && strcmp(f21, f21_ref) != 0)
		err_count++;
	if (strcmp(f22, f22_ref) != (-1 * '\n') && strcmp(f22, f22_ref) != 0)
		err_count++;
	if (strcmp(f23, f23_ref) != (-1 * '\n') && strcmp(f23, f23_ref) != 0)
		err_count++;
	if (strcmp(f24, f24_ref) != (-1 * '\n') && strcmp(f24, f24_ref) != 0)
		err_count++;

	if (err_count == 0)
	{
		printf(GREEN "[OK]");
		printf(WHITE "\n");
	}
	else
	{
		printf(RED "[KO]");
		printf(WHITE "\n");
	}



	free(f1);
	free(f2);
	free(f3);
	free(f4);
	free(f5);

	free(f21);
	free(f22);
	free(f23);
	free(f24);

	free(f1_ref);
	free(f2_ref);
	free(f3_ref);
	free(f4_ref);
	free(f5_ref);

	free(f21_ref);
	free(f22_ref);
	free(f23_ref);
	free(f24_ref);
}


void	diman_tests()
{
	test01();
	test02();
	test03();
	test04();
	test05();
	test06();
	test07();
	test08();
	test09();
	test10();
	test11();
	test12();
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


	diman_tests();
	return (0);

	get_next_line(5, &line);
	return (0);

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




	return (0);
}

