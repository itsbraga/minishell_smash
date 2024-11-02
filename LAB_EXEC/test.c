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

size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

size_t	ft_strlcpy(char *dest, const char *src, size_t size)
{
	unsigned int	i;

	i = 0;
	if (size == 0)
		return (ft_strlen(src));
	while (src[i] != '\0' && i < size - 1)
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (ft_strlen(src));
}

char	*ft_strdup(const char *s1)
{
	size_t	size;
	char	*s2;

	if (s1 == NULL)
		return (NULL);
	size = ft_strlen(s1) + 1;
	s2 = malloc(size * sizeof(char));
	if (s2 == NULL)
		return (NULL);
	ft_strlcpy(s2, s1, size);
	return (s2);
}

void	free_and_set_null(void **to_free)
{
	free(*to_free);
	*to_free = NULL;
}

int	main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	char *str;

	str = ft_strdup("helloworld");
	free_and_set_null((void *)&str);
	dprintf(2, "%s | %p\n", str, str);

	str = ft_strdup("helloworld");
	free(str);
	str = NULL;
	dprintf(2, "%s | %p\n", str, str);

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