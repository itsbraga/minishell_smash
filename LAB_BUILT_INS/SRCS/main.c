/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: art3mis <art3mis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 14:13:47 by annabrag          #+#    #+#             */
/*   Updated: 2024/10/16 15:39:44 by art3mis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "my_builtins.h"

void	secure_malloc(void *to_secure)
{
	if (to_secure == NULL)
	{
		err_msg("malloc", "cannot allocate memory", 0);
		exit(FAILURE);
	}
}

/*	Readline should not count escape sequences as visible characters.
	This is achieved by encapsulating the non-visible parts (escape
	sequences) of the prompt between special sequences :
	
	-	\001 (start of non-visible sequence)
	-	\002 (end of non-visible sequence)
	
	This enables readline to manage the length of the prompt correctly.
*/
static void	__part_one(t_prompt *pr)
{
	pr->header = ft_strjoin(rainbow_prompt(PROMPT_BAR), "[");
	secure_malloc(pr->header);
	pr->colored_user = ft_strjoin("\001" BRIGHT_YELLOW "\002", pr->username);
	secure_malloc(pr->colored_user);
	pr->part1 = ft_strjoin(pr->header, pr->colored_user);
	secure_malloc(pr->part1);
	free(pr->header);
	free(pr->colored_user);
	pr->colored_42 = ft_strjoin("\001" RED "\002", "42");
	secure_malloc(pr->colored_42);
	pr->tmp = ft_strjoin("\001" RESET "\002" "@", pr->colored_42);
	secure_malloc(pr->tmp);
	free(pr->colored_42);
}

char	*generate_prompt(t_prompt *pr)
{
	char	cwd[PATH_MAX];

	pr->username = getenv("USER");
	if (pr->username == NULL)
		pr->username = "unknown";
	if (getcwd(cwd, sizeof(cwd)) == NULL)
		perror("getcwd() error");
	__part_one(pr);
	pr->part2 = ft_strjoin(pr->tmp, "\001" RESET "\002" "] ");
	secure_malloc(pr->part2);
	free(pr->tmp);
	pr->part3 = ft_strjoin(pr->part2, cwd);
	secure_malloc(pr->part3);
	free(pr->part2);
	pr->part4 = ft_strjoin(pr->part3, " $> ");
	secure_malloc(pr->part4);
	free(pr->part3);
	pr->prompt = ft_strjoin(pr->part1, pr->part4);
	secure_malloc(pr->prompt);
	free(pr->part1);
	free(pr->part4);
	return (pr->prompt);
}

static void    __init_global(t_global *g)
{
	t_prompt	pr;
	
	g->prompt = generate_prompt(&pr);
	if (g->prompt == NULL)
		(exit(FAILURE));
	g->input = NULL;
	g->env = NULL;
	g->exp_env = NULL;
	g->token = NULL;
	g->last_exit_status = 0;
}

int	main(int argc, char **argv, char **envp)
{
	t_global	g;
	t_token		*cell = NULL;
	char		**cmd = NULL;
	int			i;

	(void)argv;
	if (argc != 1)
		return (FAILURE);
	printf("\n%s", BOLD WELCOME_BANNER RESET);
	__init_global(&g);
	create_env(&g, envp);
	while (1)
	{
		i = 0;
		g.input = readline(g.prompt);
		if (*g.input != '\0')
		{
			add_history(g.input);
			cmd = ft_split(g.input, ' ');
			if (cmd == NULL)
				return (FAILURE);
			while (cmd[i] != NULL)
			{
				cell = new_node(cmd[i]);
				if (cell == NULL)
					return (FAILURE);
				add_back(&g.token, cell);
				i++;
			}
			exec_built_in(cmd, &g);
			// display_tokens(g.token);
			lstclear_token(&g.token);
			free(cmd);
		}
	}
}
