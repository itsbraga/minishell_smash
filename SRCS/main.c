/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmateo <pmateo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 21:02:12 by pmateo            #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2024/10/23 18:51:34 by pmateo           ###   ########.fr       */
=======
/*   Updated: 2024/10/23 18:19:22 by annabrag         ###   ########.fr       */
>>>>>>> 407f7ebf419472a222507389a69cff9b344fe92c
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_sig_code = 0;

static void	__minishell(t_data *d)
{
	char	*input;
	int		error;

	error = 0;
	while (1)
	{
		display_shell_info();
		set_signals();
		input = readline(d->prompt);
		if (input == NULL) // Gestion de CTRL+D (EOF)
		{
			ft_printf(STDERR_FILENO, "exit\n");
			break ;
		}
		else if (input[0] != '\0')
		{
			add_history(input);
			if (create_main_lst(d, input) == FAILURE)
				error = 1;
			else
				display_main_lst(&(d->main));
			if (create_token_dblst(d) == FAILURE)
				error = 1;
			else
				display_token_dblst(&(d->token));
			printf("\n---------------------------------- INT MAIN ------------------------------------\n");
			display_exec_lst(&(d->exec));
<<<<<<< HEAD
			while_cmd(d, &(d->exec));
=======
			if (error != 1)
				while_cmd(d, &(d->exec));
>>>>>>> 407f7ebf419472a222507389a69cff9b344fe92c
		}
		clean_after_execution(d, input);
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
