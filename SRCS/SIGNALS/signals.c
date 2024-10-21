/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: art3mis <art3mis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 19:19:11 by annabrag          #+#    #+#             */
/*   Updated: 2024/10/21 22:57:42 by art3mis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	__handle_sigint(int sig)
{
	t_prompt	pr;
	t_data		*d;
	char		*nl_pos;
	size_t		line1_len;
	
	(void)sig;
	ft_putchar_fd('\n', STDOUT_FILENO);
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
	g_sig_code = 1; // verifier
}

void	handle_sigquit(void)
{
	struct sigaction	sa;

	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sa.sa_handler = SIG_IGN;
	sigaction(SIGQUIT, &sa, NULL);
	g_sig_code = 1; // verifier
}

void	set_signals(void)
{
	struct sigaction	sa;

	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sa.sa_handler = __handle_sigint;
	sigaction(SIGINT, &sa, NULL);
	handle_sigquit();
}
