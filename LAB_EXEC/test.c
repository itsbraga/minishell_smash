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
	char **cmd;
	char *bin_path;

	cmd[0] = "Makefile";
	// cmd[1] = "";
	// cmd[2] = "-l";
	bin_path = "/usr/bin/cat";
	if (execve(bin_path, cmd, envp) == -1)
	{
		printf("%s\n", strerror(errno));
		exit(EXIT_FAILURE);
	}
}