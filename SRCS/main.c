/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: annabrag <annabrag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 21:02:12 by pmateo            #+#    #+#             */
/*   Updated: 2024/08/25 16:05:16 by annabrag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*__get_username(void)
{
	const char		*name;
	char			*bracket;
	char			*full_name;
	
	name = getenv("USER");
	bracket = "[";
	full_name = ft_strjoin(bracket, name);
	return (full_name);
}

// void	free_tab(char **tab)
// {
// 	int	i;

// 	i = 0;
// 	while (tab[i] != NULL)
// 	{
// 		free(tab[i]);
// 		i++;
// 	}
// 	free(tab);
// 	tab = NULL;
// }

int	main(int argc, char **argv, char **envp)
{
	t_global	g;
	char		*user;
	char		*prompt;

	if (argc > 1)
		exit(EXIT_FAILURE);
	(void)argv;
	printf("\n%s", BOLD WELCOME_BANNER RESET);
	init_global(&g);
	// create_env(&g, envp);
	create_env_list(&g.env, envp);
	user = __get_username();
	prompt = ft_strjoin(user, "@42] $> ");
	while (1)
	{
		g.input = readline(prompt);
		if (*g.input != '\0')
			add_history(g.input);
		// free(g.input);
	}
	printf("%s%s%s", PURPLE, "Bye le sang\n", RESET);
	free(user);
	free(prompt);
	return (EXIT_SUCCESS);
}
