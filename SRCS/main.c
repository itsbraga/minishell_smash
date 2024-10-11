/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: art3mis <art3mis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 21:02:12 by pmateo            #+#    #+#             */
/*   Updated: 2024/10/12 01:49:24 by art3mis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_sig_code;

static int	__minishell(t_data *d)
{
	char	*user_input;

	while (1)
	{
		printf("PID : %d\n", getpid());
		if (isatty(STDIN_FILENO) == 1)
			printf("STDIN connected to terminal :)\n");
		else
			printf("STDIN isn't connected to terminal /!\\\n");
		user_input = readline(d->prompt);
		if (user_input != NULL && user_input[0] != '\0')
		{
			add_history(user_input);
			if (create_main_lst(d, user_input) == FAILURE)
				return (FAILURE);
			display_main_lst(d->main);
			if (create_token_dblst(d) == FAILURE)
				return (FAILURE);
			display_token_dblst(d->token);
			// if (create_token_and_exec_lsts(d) == FAILURE)
			// {
			// 	printf("TOKEN AND EXEC LSTS: creation failed\n");
			// 	return (FAILURE);
			// }
			printf("\n---------------------------------- INT MAIN ------------------------------------\n");
			display_exec_lst(d->exec);
			// while_cmd(d, &(d->exec));
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
