/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: annabrag <annabrag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 14:13:47 by annabrag          #+#    #+#             */
/*   Updated: 2024/08/29 20:21:21 by annabrag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "my_builtins.h"

int		g_last_exit_status;

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
	prompt = ft_strjoin(part1, BOLD "@42]" RESET " $> ");
	free(part1);
	return (prompt);
}

static void    __init_global(t_global *g)
{
	g->prompt = __generate_prompt();
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
	create_env_list(&g.env, envp);
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
			display_tokens(g.token);
			lstclear_tokens(&g.token);
		}
	}
	free_tab(cmd);
	free(g.input);
}
