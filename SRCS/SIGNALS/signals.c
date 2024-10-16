/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: art3mis <art3mis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 19:19:11 by annabrag          #+#    #+#             */
/*   Updated: 2024/10/16 18:27:44 by art3mis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <signal.h>

int	g_sig_code;

/*	rl_on_new_line()
	
	Tell the update routines that we have moved
	onto a new (empty) line, usually after
	outputting a newline '\n'
*/
static void	__sigint_handler(int sig)
{
	if (sig == SIGINT)
	{
		write(STDOUT_FILENO, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

static void	__ignore_sigquit(void)
{
	struct sigaction	sa;

	ft_bzero(&sa, sizeof(sa));
	sa.sa_handler = SIG_IGN;
	sigaction(SIGQUIT, &sa, NULL);
}

void	init_signals_interactive_mode(void)
{
	struct sigaction	sa;

	ft_bzero(&sa, sizeof(sa));
	__ignore_sigquit();
	sa.sa_handler = &(__sigint_handler);
	sigaction(SIGINT, &sa, NULL);
}
