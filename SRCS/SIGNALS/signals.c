/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmateo <pmateo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 19:19:11 by annabrag          #+#    #+#             */
/*   Updated: 2024/10/29 20:41:22 by pmateo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	rl_reset_custom_prompt(void)
{
	t_prompt	pr;
	t_data		*d;
	char		*nl_pos;
	size_t		line1_len;

	d = data_struct();
	rl_on_new_line();
	rl_replace_line("", 0);
	update_prompt(d, &pr);
	nl_pos = ft_strchr(d->prompt, '\n');
	if (nl_pos != NULL)
	{
		line1_len = nl_pos - d->prompt + 1;
		display_shell_info();
		write(STDOUT_FILENO, d->prompt, line1_len);
		rl_redisplay();
	}
}

static void	__sigint_handler(int signo)
{
	(void)signo;
	ft_putchar_fd('\n', STDOUT_FILENO);
	ft_exit_status(CTRL_C, ADD);
	rl_reset_custom_prompt();
}

void	set_signals(void)
{
	signal(SIGINT, &__sigint_handler);
	signal(SIGQUIT, SIG_IGN);
}

static void	__sigint_handler_heredoc(int sig)
{
	(void)sig;
	g_sig_code = CTRL_C;
	ft_exit_status(CTRL_C, ADD);
}

// appeler cet handler dans la fonction d'ouverture d'here_doc
void	set_signals_in_heredoc()
{
	signal(SIGINT, &__sigint_handler_heredoc);
	signal(SIGQUIT, SIG_IGN);
}
