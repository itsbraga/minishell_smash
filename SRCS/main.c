/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: annabrag <annabrag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 21:02:12 by pmateo            #+#    #+#             */
/*   Updated: 2024/10/17 23:34:18 by annabrag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	__minishell(t_data *d)
{
	char	*user_input;

	while (1)
	{
		display_shell_info();
		setup_signals();
		user_input = readline(d->prompt);
		if (user_input == NULL)
		{
			ft_printf(STDERR_FILENO, "exit\n");
			break ;
		}
		else if (user_input != NULL && user_input[0] != '\0')
		{
			add_history(user_input);
			if (create_main_lst(d, user_input) == FAILURE)
				return (FAILURE);
			display_main_lst(d->main);
			if (create_token_dblst(d) == FAILURE)
				return (FAILURE);
			printf("\n---------------------------------- INT MAIN ------------------------------------\n");
			display_exec_lst(d->exec);
			while_cmd(d, &(d->exec));
			// 	exec_built_in(d->exec->cmd, d);
		}
		free(user_input);
	}
	return (SUCCESS);
}

int	main(int argc, char **argv, char **envp)
{
	t_data	*d;

	(void)argv;
	d = data_struct();
	if (argc != 1)
	{
		ft_printf(STDOUT_FILENO, BOLD YELLOW "No arguments allowed\n" R);
		clean_exit_shell(FAILURE);
	}
	printf("\n%s", BOLD WELCOME_BANNER R);
	create_env(d, envp);
	__minishell(d);
	return (SUCCESS);
}
