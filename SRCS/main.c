/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: annabrag <annabrag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 21:02:12 by pmateo            #+#    #+#             */
/*   Updated: 2024/08/13 14:44:47 by annabrag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*get_user_name(void)
{
	const char		*name;
	char			*bracket;
	char			*full_name;
	
	name = getenv("USER");
	bracket = "[";
	full_name = ft_strjoin(bracket, name);
	return (full_name);
}

int	main(int argc, char **argv, char **envp)
{
	t_global	g;
	char		*user;
	char		*prompt;

	if (argc > 1)
		exit(EXIT_FAILURE);
	(void)argv;
	init_global(&g);
	create_env(&g, envp);
	user = get_user_name();
	prompt = ft_strjoin(user, "@42] $> ");
	while (1)
	{
		g.input = readline(prompt);
		if (*g.input)
			add_history(g.input);
		// free(g.input);
	}
	free(user);
	free(prompt);
	return (0);
}
