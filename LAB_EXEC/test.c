# include <stddef.h>
# include <stdio.h>
# include <unistd.h>
# include <sys/types.h>
# include <stdlib.h>
# include <stdbool.h>
# include <limits.h>
# include <errno.h>
# include <readline/readline.h>


int	main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	char *cmd[2];
	char *bin_path;

	cmd[0] = "ct";
	cmd[1] = NULL;
	// cmd[2] = "-l";
	bin_path = "/usr/bin/ct";
	// if (execve(bin_path, cmd, envp) == -1)
	// {
	// 	printf("%s\n", strerror(errno));
	// 	exit(EXIT_FAILURE);
	// }
	if (access(bin_path, X_OK == -1))
	{
		printf("%s\n", strerror(errno));
		exit(EXIT_FAILURE);
	}
}