/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: annabrag <annabrag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 21:02:12 by pmateo            #+#    #+#             */
/*   Updated: 2024/11/02 21:40:05 by annabrag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_sig_code = 0;

static void	__loop(t_data *d, char **input, int *error)
{
	add_history(*input);
	if (create_main_lst(d, *input) == FAILURE)
		*error = 1;
	if (create_token_dblst(d) == FAILURE)
		*error = 1;
	if (*error != 1)
		while_cmd(d, &(d->exec));
	*error = 0;
}

static void	__minishell(t_data *d)
{
	char	*input;
	int		error;

	error = 0;
	d->fd_stdin_backup = dup(STDIN_FILENO);
	while (1)
	{
		if (isatty(STDIN_FILENO) == 0)
			dup2(d->fd_stdin_backup, STDIN_FILENO);
		set_signals();
		input = readline(d->prompt);
		if (input == NULL)
		{
			ft_printf(STDERR_FILENO, "exit\n");
			clean_exit_shell(SUCCESS);
		}
		else if (input[0] != '\0')
			__loop(d, &input, &error);
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
