/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmateo <pmateo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 21:02:12 by pmateo            #+#    #+#             */
/*   Updated: 2024/08/26 18:48:37 by pmateo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    display_env(t_env *env)
{
    t_env    *tmp;

    tmp = env;
    while (tmp != NULL)
    {
        ft_putstr_fd(tmp->content, 1);
        ft_putendl_fd("", 1);
        tmp = tmp->next;
    }
}

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

int	main(int argc, char **argv, char **envp)
{
	t_global	g;
	char		*user;
	char		*prompt;

	(void)argv;
	if (argc != 1)
		exit(EXIT_FAILURE);
	printf("\n%s", BOLD WELCOME_BANNER RESET);
	init_global(&g);
	create_env(&g, envp);
	user = __get_username();
	prompt = ft_strjoin(user, "@42] $> ");
	while (1)
	{
		g.input = readline(prompt);
		if (*g.input != '\0')
			add_history(g.input);
	}
	// free(g.input);
	printf("%s%s%s", PURPLE, "Bye le sang\n", RESET);
	free(user);
	free(prompt);
	return (EXIT_SUCCESS);
}
