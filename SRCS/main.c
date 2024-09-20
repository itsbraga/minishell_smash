/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmateo <pmateo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 21:02:12 by pmateo            #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2024/09/20 17:49:38 by annabrag         ###   ########.fr       */
=======
/*   Updated: 2024/09/20 17:49:31 by pmateo           ###   ########.fr       */
>>>>>>> 5abb94ad707e158c85029dc47f2f59e712f46d05
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_sig_code;

int	minishell(t_data *d)
{
	char	*user_input;

	while (1)
	{
		user_input = readline(d->prompt);
		if (user_input != NULL)
		{
			add_history(user_input);
			if (create_main_lst(d, user_input) == FAILURE)
			{
				printf("unable to create the main list, program cannot execute\n");
				return (FAILURE);
			}
			display_main_lst(d->main);
			if (create_token_dblst(d->main, d->exec) == FAILURE)
			{
				printf("unable to create the token list, program cannot execute\n");
				return (FAILURE);
			}
			free(user_input);
		}
	}
	return (SUCCESS);
}

int	main(int argc, char **argv, char **envp)
{
	t_data	*d;

	(void)argv;
	d = get_data_instance();
	if (argc != 1)
	{
		ft_printf(2, BOLD YELLOW "No arguments allowed\n" RESET);
		exit(FAILURE);
	}
	printf("\n%s", BOLD WELCOME_BANNER RESET);
	create_env(d, envp);
	minishell(d);
	return (SUCCESS);
}
