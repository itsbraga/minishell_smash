/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: art3mis <art3mis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 21:02:12 by pmateo            #+#    #+#             */
/*   Updated: 2024/09/06 02:19:30 by art3mis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_sig_code;

int	minishell(t_global *g)
{
	char		*user_input;
	
	while (1)
	{
		user_input = readline(g->prompt);
		if (user_input != NULL)
		{
			add_history(user_input);
			if (create_main_lst(g, user_input) == FAILURE)
			{
				printf("unable to create the main list, program cannot execute\n");
				return (FAILURE);
			}
			printf(GREEN "CLEANED TOKENS:\n");
			display_main_lst(g->main);
			free(user_input);
		}
	}
	return (SUCCESS);
}

int	main(int argc, char **argv, char **envp)
{
	t_global	g;
	// char		*user_input;

	(void)argv;
	if (argc != 1)
	{
		ft_printf(2, BOLD YELLOW "No arguments allowed\n" RESET);
		exit(FAILURE);
	}
	printf("\n%s", BOLD WELCOME_BANNER RESET);
	init_global(&g);
	create_env(&g, envp);
	minishell(&g);
	// while (1)
	// {
	// 	user_input = readline(g.prompt);
	// 	if (user_input != NULL)
	// 	{
	// 		add_history(user_input);
	// 		if (create_main_lst(&g, user_input) == SUCCESS)
	// 		{
	// 			printf(GREEN "CLEANED TOKENS:\n");
	// 			display_main_lst(g.main);
	// 			free(user_input);
	// 		}
	// 	}
	// }
	return (SUCCESS);
}
