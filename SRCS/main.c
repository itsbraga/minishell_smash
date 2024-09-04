/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: art3mis <art3mis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 21:02:12 by pmateo            #+#    #+#             */
/*   Updated: 2024/09/04 00:11:48 by art3mis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		g_last_exit_status;

int	main(int argc, char **argv, char **envp)
{
	t_global	g;
	char		*user_input;

	(void)argv;
	if (argc != 1)
		return (FAILURE);
	printf("\n%s", BOLD WELCOME_BANNER RESET);
	init_global(&g);
	create_env(&g, envp);
	while (1)
	{
		user_input = readline(g.prompt);
		if (user_input != NULL)
		{
			add_history(user_input);
			create_main_lst(&g, user_input);
			printf(BOLD RED "tokens with whitespaces: \n" RESET);
			display_main_lst(g.main);
			del_unwanted_char(g.main);
			printf(BOLD BLUE "tokens after trim: \n" RESET);
			display_main_lst(g.main);
			free(user_input);
		}
	}
	// printf("%s\n", PURPLE BYE_MSG RESET);
	return (SUCCESS);
}
