/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: annabrag <annabrag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 21:02:12 by pmateo            #+#    #+#             */
/*   Updated: 2024/08/28 14:28:58 by annabrag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		g_last_exit_status;

int	main(int argc, char **argv, char **envp)
{
	t_global	g;

	(void)argv;
	if (argc != 1)
		return (FAILURE);
	printf("\n%s", BOLD WELCOME_BANNER RESET);
	init_global(&g);
	create_env(&g, envp);
	while (1)
	{
		g.input = readline(g.prompt);
		if (*g.input != '\0')
			add_history(g.input);
		// free(g.input);
	}
	printf("%s\n", PURPLE BYE_MSG RESET);
	return (SUCCESS);
}
