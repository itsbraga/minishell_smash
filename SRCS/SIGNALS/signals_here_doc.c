/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals_here_doc.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: annabrag <annabrag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 12:08:26 by annabrag          #+#    #+#             */
/*   Updated: 2024/10/31 12:09:33 by annabrag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	__sigint_handler_heredoc(int signo)
{
	(void)signo;
	close(STDIN_FILENO);
	rl_on_new_line();
	rl_replace_line("", 0);
	ft_putchar_fd('\n', STDOUT_FILENO);
	g_sig_code = CTRL_C;
	ft_exit_status(CTRL_C, ADD);
}

void	set_signals_in_heredoc(void)
{
	signal(SIGINT, &__sigint_handler_heredoc);
	signal(SIGQUIT, SIG_IGN);
}
