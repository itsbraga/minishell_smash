/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: annabrag <annabrag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 21:02:12 by pmateo            #+#    #+#             */
/*   Updated: 2024/06/26 18:50:50 by annabrag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../INCLUDES/minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_global	g;

	if (argc > 1)
		exit(EXIT_FAILURE);
	(void)argv;
	init_global(&g);
	g.env = create_env(envp);
	// g.export_env = create_export_env(envp);
	while (1)
	{
		g.input = readline(BOLD PINK "[elgato@42]" RESET " $> ");
		if (*g.input)
			add_history(g.input);
		// free(g.input);
	}
	return (0);
}
