/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: annabrag <annabrag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 21:02:12 by pmateo            #+#    #+#             */
/*   Updated: 2024/08/26 20:18:15 by annabrag         ###   ########.fr       */
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

static char	*__generate_prompt(void)
{
	char	*username;
	char	*part1;
	char	*part2;
	char	*prompt;
	
	username = getenv("USER");
	if (username == NULL)
		username = "unknown";
	part1 = ft_strjoin(BOLD PINK "[", username);
	part2 = ft_strjoin(part1, "@42]" RESET " $> ");
	free(part1);
	prompt = part2;
	return (prompt);
}

int	main(int argc, char **argv, char **envp)
{
	t_global	g;
	char		*prompt;

	(void)argv;
	if (argc != 1)
		exit(FAILURE);
	printf("\n%s", BOLD WELCOME_BANNER RESET);
	prompt = __generate_prompt();
	if (prompt == NULL)
		free(prompt);
	init_global(&g);
	create_env(&g, envp);
	while (1)
	{
		g.input = readline(prompt);
		if (*g.input != '\0')
			add_history(g.input);
	}
	printf("%s\n", PURPLE BYE_MSG RESET);
	return (SUCCESS);
}
