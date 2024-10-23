/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: annabrag <annabrag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 21:02:12 by pmateo            #+#    #+#             */
/*   Updated: 2024/10/23 16:28:37 by annabrag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_sig_code = 0;

static void	__minishell(t_data *d)
{
	char	*input;

	while (1)
	{
		display_shell_info();
		set_signals();
		input = readline(d->prompt);
		if (input == NULL) // Gestion de CTRL+D (EOF)
		{
			ft_printf(STDERR_FILENO, "exit\n");
			break ; //clean_exit_shell(SUCCESS);
		}
		else if (input[0] != '\0')
		{
			add_history(input);
			if (create_main_lst(d, input) == SUCCESS)
				display_main_lst(&(d->main));
			if (create_token_dblst(d) == SUCCESS)
				display_token_dblst(&(d->token));
			printf("\n---------------------------------- INT MAIN ------------------------------------\n");
			display_exec_lst(&(d->exec));
			// while_cmd(d, &(d->exec));
		}
		printf("before clean\n");
		display_main_lst(&(d->main));
		clean_after_execution(d, input);
		printf("after clean\n");
		display_main_lst(&(d->main));
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
