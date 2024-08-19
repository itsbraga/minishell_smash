/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: annabrag <annabrag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 14:13:47 by annabrag          #+#    #+#             */
/*   Updated: 2024/08/19 20:09:13 by annabrag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "built_ins.h"

t_global	g;

static void    __init_global(t_global *g)
{
	g->input = NULL;
	g->env = NULL;
	g->export_env = NULL;
}

void	free_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

int	main(int argc, char **argv, char **envp)
{
	t_token		*t = NULL;
	t_token		*cell = NULL;
	char		**cmd = NULL;
	int			i = 0;

	(void)argv;
	if (argc != 1)
		exit(EXIT_FAILURE);
	__init_global(&g);
	create_env(&g, envp);
	// show_env(g.env);
	while (1)
	{
		g.input = readline(BOLD PINK "[minishell] " RESET "$> ");
		if (*g.input != '\0')
		{
			add_history(g.input);
			cmd = ft_split(g.input, ' ');
			if (!cmd)
				return (EXIT_FAILURE);
			while (cmd[i] != NULL)
			{
				cell = new_node(cmd[i]);
				if (!cell)
					return (EXIT_FAILURE);
				add_back(&t, cell);
				// printf("%s\n", cmd[i]);
				i++;
			}
			exec_built_in(cmd);
			update_env_paths(&g);
			// my_cd(t, &g);
		}
		// free(g.input);
	}
	// free_tab(cmd);
	display_tokens(t);
}
