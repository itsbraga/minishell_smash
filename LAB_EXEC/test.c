# include <stddef.h>
# include <string.h>
# include <stdio.h>
# include <unistd.h>
# include <sys/types.h>
# include <stdlib.h>
# include <stdbool.h>
# include <limits.h>
# include <errno.h>
// # include <readline/readline.h>


int	main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	char *line;

	line = malloc(10);
	// pid_t	child_pid;
	// int tmp_fd;
	// int	fd[2];

	// if (pipe(fd) == -1)
	// 	return (EXIT_FAILURE);
	// tmp_fd = 0;
	// printf("PIPE FDS MAIN\n");
	// printf("fd[1] = %d | fd[0] = %d\n", fd[1], fd[0]);
	// dup2(tmp_fd, fd[0]);
	// printf("dup2(tmp_fd, fd[0])\nfd[0] = %d | tmp_fd = %d\n", fd[0], tmp_fd);
	// dup2(fd[1], fd[0]);
	// printf("dup2(fd[1], fd[0])\nfd[0] = %d | fd[1] = %d\n", fd[0], fd[1]);
	// read(0, line, 10);
	// dprintf(2, "encore la\n");
	write(2, "\n", 1);



	return (EXIT_SUCCESS);












	// char *cmd[3];
	// char *bin_path;

	// cmd[0] = "cat";
	// cmd[1] = "Makefile*/blablaprout123344";
	// // cmd[0] = "ls";
	// // cmd[1] = "-l";
	// cmd[2] = NULL;
	// bin_path = "/usr/bin/cat";
	// if (execve(bin_path, cmd, envp) == -1)
	// {
	// 	printf("%s\n", strerror(errno));
	// 	exit(EXIT_FAILURE);
	// }
	// // if (access(bin_path, X_OK == -1))
	// {
	// 	printf("%s\n", strerror(errno));
	// 	exit(EXIT_FAILURE);
	// }
}