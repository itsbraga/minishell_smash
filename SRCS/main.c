/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: art3mis <art3mis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 21:02:12 by pmateo            #+#    #+#             */
/*   Updated: 2024/11/04 03:03:02 by art3mis          ###   ########.fr       */
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
			clean_exit(SUCCESS);
		}
		else if (input[0] != '\0')
			__loop(d, &input, &error);
		clean_after_execution(d, input);
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_data	*d;
	const char	*acronym = rainbow_banner(CREATORS);

	(void)argv;
	d = data_struct();
	if (argc != 1)
	{
		ft_printf(STDOUT_FILENO, BOLD YELLOW "No arguments allowed\n" R);
		clean_exit(FAILURE);
	}
	printf("\n%s%s%s", BANNER_PT1, acronym, BANNER_PT2);
	create_env(d, envp);
	__minishell(d);
	(void)yama(REMOVE, (void *)&acronym, 0);
	return (SUCCESS);
}
