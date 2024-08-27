/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: art3mis <art3mis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 14:13:47 by annabrag          #+#    #+#             */
/*   Updated: 2024/08/27 02:26:59 by art3mis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "my_builtins.h"

int		g_last_exit_status;

static void    __init_global(t_global *g)
{
	g->input = NULL;
	g->env = NULL;
	g->token = NULL;
	// g->last_exit_status = 0;
	g_last_exit_status = 0;
}

static char	*__generate_prompt(void)
{
	char	*username;
	char	*rb_username;
	char	*part1;
	char	*prompt;
	
	username = getenv("USER");
	if (username == NULL)
		username = "unknown";
	rb_username = rainbow_prompt(username);
	part1 = ft_strjoin(BOLD "[", rb_username);
	free(rb_username);
	prompt = ft_strjoin(part1, "@42]" RESET " $> ");
	free(part1);
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
	if ((prompt = __generate_prompt()) == NULL)
		exit(FAILURE);
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
	free(prompt);
	free_tab(cmd);
}
