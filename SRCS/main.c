/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: annabrag <annabrag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 21:02:12 by pmateo            #+#    #+#             */
/*   Updated: 2024/06/28 18:14:05 by annabrag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../INCLUDES/minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_global		g;
	const char		*name;

	if (argc > 1)
		exit(EXIT_FAILURE);
	(void)argv;
	init_global(&g);
	create_env(&g, envp);
	name = getenv("USER");
	while (1)
	{
		g.input = readline(name);
		if (*g.input)
			add_history(g.input);
		// free(g.input);
	}
	return (0);
}
