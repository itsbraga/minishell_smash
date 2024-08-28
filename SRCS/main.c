/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: annabrag <annabrag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 21:02:12 by pmateo            #+#    #+#             */
/*   Updated: 2024/08/28 11:54:19 by annabrag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		g_last_exit_status;

static char	*__generate_prompt(void)
{
	char	*username;
	char	*rb_username;
	char	*part1;
	char	*prompt;
	
	username = getenv("USER");
	if (username == NULL)
		username = "unknown";
	rb_username = rainbow_prompt(username);
	part1 = ft_strjoin(BOLD "[", rb_username);
	free(rb_username);
	prompt = ft_strjoin(part1, BOLD "@42]" RESET " $> ");
	free(part1);
	return (prompt);
}

int	main(int argc, char **argv, char **envp)
{
	t_global	g;
	char		*prompt;

	(void)argv;
	if (argc != 1)
		return (FAILURE);
	printf("\n%s", BOLD WELCOME_BANNER RESET);
	prompt = __generate_prompt();
	if (prompt == NULL)
		exit(FAILURE);
	init_global(&g);
	create_env(&g, envp);
	while (1)
	{
		g.input = readline(prompt);
		if (*g.input != '\0')
			add_history(g.input);
		// free(g.input);
	}
	free(prompt);
	printf("%s\n", PURPLE BYE_MSG RESET);
	return (SUCCESS);
}
