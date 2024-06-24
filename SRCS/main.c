/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmateo <pmateo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 21:02:12 by pmateo            #+#    #+#             */
/*   Updated: 2024/06/24 08:10:43 by pmateo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../INCLUDES/minishell.h"

int main(int argc, char **argv, char **envp)
{
	t_global g;
	
	if (argc > 1)
		exit(EXIT_FAILURE);
	(void)argv;
	init_global(&g);
	g.env = create_env(envp);
	// g.export_env = create_export_env(envp);
	while (1)
	{
		g.input = readline("@_@ $> ");
		if (*g.input)
			add_history(g.input);
		
	}
	return (0);
}