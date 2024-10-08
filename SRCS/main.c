/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: annabrag <annabrag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 21:02:12 by pmateo            #+#    #+#             */
/*   Updated: 2024/10/08 19:54:07 by annabrag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_sig_code;

void	print_tab3(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		dprintf(2, BLUE "tab[i] = %s ; ptr of tab[i] = %p\n" R, tab[i], tab[i]);
		i++;
	}
}

static int	__minishell(t_data *d)
{
	char	*user_input;

	while (1)
	{
		user_input = readline(d->prompt);
		if (user_input != NULL && user_input[0] != '\0')
		{
			add_history(user_input);
			if (create_main_lst(d, user_input) == FAILURE)
				return (FAILURE);
			display_main_lst(d->main);
			if (create_token_dblst(d) == FAILURE)
				return (FAILURE);
			// if (d->exec != NULL)
			// 	while_cmd(d, &(d->exec));
			dprintf(2, "cmd[0]: %p\n", d->exec->cmd);
			dprintf(2, "heredoc_nb: %d\n", d->exec->heredoc_nb);
			dprintf(2, "cmd_count: %d\n", d->info->cmd_count);
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
	// clean_exit_shell(SUCCESS);
	return (SUCCESS);
}
