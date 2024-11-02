/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: art3mis <art3mis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 19:19:11 by annabrag          #+#    #+#             */
/*   Updated: 2024/11/02 00:19:57 by art3mis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sigquit_handler(int signo)
{
	(void)signo;
	ft_putendl_fd("Quit (core dumped)", STDOUT_FILENO);
	rl_on_new_line();
	rl_replace_line("", 0);
	g_sig_code = CTRL_BCKSLH;
	ft_exit_status(CTRL_BCKSLH, ADD);
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

static void	__sigint_handler_exec(int signo)
{
	(void)signo;
	ft_putchar_fd('\n', STDOUT_FILENO);
	rl_on_new_line();
	rl_replace_line("", 0);
	g_sig_code = CTRL_C;
	ft_exit_status(CTRL_C, ADD);
}

void	set_signals_in_exec(void)
{
	signal(SIGINT, &__sigint_handler_exec);
	signal(SIGQUIT, &sigquit_handler);
}
