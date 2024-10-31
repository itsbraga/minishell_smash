/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmateo <pmateo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 19:19:11 by annabrag          #+#    #+#             */
/*   Updated: 2024/10/31 06:28:26 by pmateo           ###   ########.fr       */
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

void	sigquit_handler(int signo)
{
	(void)signo;
	ft_putendl_fd("Quit (core dumped)", STDOUT_FILENO);
	rl_on_new_line();
	rl_replace_line("", 0);
	g_sig_code = CTRL_BCKSLH;
	ft_exit_status(CTRL_BCKSLH, ADD);
}

static void	__sigint_handler_exec(int signo)
{
	(void)signo;
	dprintf(2, "sigint handler exec\n");
	ft_putchar_fd('\n', STDOUT_FILENO);
	rl_on_new_line();
	rl_replace_line("", 0);
	g_sig_code = CTRL_C;
	ft_exit_status(CTRL_C, ADD);
}

static void	__sigint_handler(int signo)
{
	(void)signo;
	dprintf(2, "sigint handler main\n");
	ft_putchar_fd('\n', STDOUT_FILENO);
	ft_exit_status(CTRL_C, ADD);
	rl_reset_custom_prompt();
}

static void	__sigint_handler_heredoc(int signo)
{
	(void)signo;
	dprintf(2, "sigint handler heredoc\n");
	close(STDIN_FILENO);
	rl_on_new_line();
	rl_replace_line("", 0);
	ft_putchar_fd('\n', STDOUT_FILENO);
	g_sig_code = CTRL_C;
	ft_exit_status(CTRL_C, ADD);
}
void	set_signals_in_exec(void)
{
	signal(SIGINT, &__sigint_handler_exec);
	signal(SIGQUIT, &sigquit_handler);
}

void	set_signals_in_heredoc(void)
{
	signal(SIGINT, &__sigint_handler_heredoc);
	signal(SIGQUIT, SIG_IGN);
}

void	set_signals(void)
{
	signal(SIGINT, &__sigint_handler);
	signal(SIGQUIT, SIG_IGN);
}
