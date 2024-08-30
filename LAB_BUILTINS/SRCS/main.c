/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: annabrag <annabrag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 14:13:47 by annabrag          #+#    #+#             */
/*   Updated: 2024/08/30 20:54:27 by annabrag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "my_builtins.h"

int		g_last_exit_status;

/*	Readline should not count escape sequences as visible characters.
	This is achieved by encapsulating the non-visible parts (escape
	sequences) of the prompt between special sequences :
	
	-	\001 (start of non-visible sequence)
	-	\002 (end of non-visible sequence)
	
	This enables readline to manage the length of the prompt correctly.
*/
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
	part1 = ft_strjoin("\001" BOLD "\002" "[", rb_username);
	free(rb_username);
	prompt = ft_strjoin(part1, "\001" BOLD "\002" "@42]\001" RESET "\002 $> ");
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
			display_tokens(g.token);
			lstclear_tokens(&g.token);
		}
	}
	free(g.input);
	free_tab(cmd);
}
