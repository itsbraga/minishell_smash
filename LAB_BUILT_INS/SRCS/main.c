/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: annabrag <annabrag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 14:13:47 by annabrag          #+#    #+#             */
/*   Updated: 2024/08/26 19:28:55 by annabrag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "built_ins.h"

static void    __init_global(t_global *g)
{
	g->input = NULL;
	g->env = NULL;
	g->token = NULL;
	g->last_exit_status = 0;
}

static char	*__generate_prompt(void)
{
	char	*username;
	char	*part1;
	char	*part2;
	char	*prompt;
	
	username = getenv("USER");
	if (username == NULL)
		username = "unknown";
	part1 = ft_strjoin(BOLD PINK "[", username);
	part2 = ft_strjoin(part1, "@42]" RESET " $> ");
	free(part1);
	prompt = part2;
	return (prompt);
}

int	main(int argc, char **argv, char **envp)
{
	t_global	g;
	char		*prompt;
	t_token		*cell = NULL;
	char		**cmd = NULL;
	int			i;

	(void)argv;
	if (argc != 1)
		exit(FAILURE);
	printf("\n%s", BOLD WELCOME_BANNER RESET);
	prompt = __generate_prompt();
	__init_global(&g);
	create_env_list(&g.env, envp);
	while (1)
	{
		i = 0;
		g.input = readline(prompt);
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
			display_tokens(g.token);
			lstclear_tokens(&g.token);
		}
	}
	free_tab(cmd);
}
