/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: art3mis <art3mis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 19:19:11 by annabrag          #+#    #+#             */
/*   Updated: 2024/10/20 23:36:40 by art3mis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_sig_code;

/*	rl_on_new_line()
	
	Tell the update routines that we have moved
	onto a new (empty) line, usually after
	outputting a newline '\n'
*/
static void	__sigint_handler(int sig)
{
	t_prompt	pr;
	t_data		*d;
	char		*nl_pos;
	size_t		line1_len;
	
	(void)sig;
	write(STDOUT_FILENO, "\n", 1);
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

static void	__sigquit_handler(void)
{
	struct sigaction	sa;

	sa.sa_handler = SIG_IGN;
	sa.sa_flags = 0;
	sigemptyset(&sa.sa_mask);
	sigaction(SIGQUIT, &sa, NULL);
}

void	setup_signals(void)
{
	struct sigaction	sa;

	sa.sa_handler = __sigint_handler;
	sa.sa_flags = 0;
	sigemptyset(&sa.sa_mask);
	sigaction(SIGINT, &sa, NULL);
	__sigquit_handler();
}
