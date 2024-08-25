/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: annabrag <annabrag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 14:13:47 by annabrag          #+#    #+#             */
/*   Updated: 2024/08/25 21:44:42 by annabrag         ###   ########.fr       */
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

void	free_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i] != NULL)
	{
		free(tab[i]);
		i++;
	}
	free(tab);
	tab = NULL;
}

int	main(int argc, char **argv, char **envp)
{
	t_global	g;
	t_token		*cell = NULL;
	char		**cmd = NULL;
	int			i;

	(void)argv;
	if (argc != 1)
		exit(EXIT_FAILURE);
	printf("\n%s", BOLD WELCOME_BANNER RESET);
	__init_global(&g);
	create_env_list(&g.env, envp);
	while (1)
	{
		i = 0;
		g.input = readline(BOLD PINK "[minishell] " RESET "$> ");
		if (*g.input != '\0')
		{
			add_history(g.input);
			cmd = ft_split(g.input, ' ');
			if (cmd == NULL)
				return (EXIT_FAILURE);
			while (cmd[i] != NULL)
			{
				cell = new_node(cmd[i]);
				if (cell == NULL)
					return (EXIT_FAILURE);
				add_back(&g.token, cell);
				i++;
			}
			exec_built_in(cmd, &g);
			display_tokens(g.token);
			clear_tokens(&g.token);
		}
	}
	free_tab(cmd);
}
