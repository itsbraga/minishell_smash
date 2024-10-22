/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: art3mis <art3mis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 21:02:12 by pmateo            #+#    #+#             */
/*   Updated: 2024/10/22 23:58:52 by art3mis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_sig_code = 0;

static void	__minishell(t_data *d)
{
	char	*user_input;

	while (1)
	{
		display_shell_info();
		set_signals();
		user_input = readline(d->prompt);
		if (user_input == NULL) // Gestion de CTRL+D (EOF)
		{
			ft_printf(STDERR_FILENO, "exit\n");
			break ; // clean_exit_shell(SUCCESS);
		}
		else if (user_input[0] != '\0')
		{
			add_history(user_input);
			if (create_main_lst(d, user_input) == SUCCESS)
				display_main_lst(d->main);
			if (create_token_dblst(d) == FAILURE)
				return ;
			printf("\n---------------------------------- INT MAIN ------------------------------------\n");
			display_exec_lst(d->exec);
			// while_cmd(d, &(d->exec));
		}
		clean_after_execution(d, user_input);
	}
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
