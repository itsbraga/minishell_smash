/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: annabrag <annabrag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 16:28:03 by annabrag          #+#    #+#             */
/*   Updated: 2024/10/17 17:01:22 by annabrag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "my_builtins.h"

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

static void	__sigquit_handler(void)
{
	struct sigaction	sa;

	ft_bzero(&sa, sizeof(sa));
	sa.sa_handler = SIG_IGN;
	sigaction(SIGQUIT, &sa, NULL);
}

void	setup_signals(void)
{
	struct sigaction	sa;

	ft_bzero(&sa, sizeof(sa));
	__sigquit_handler();
	sa.sa_handler = &(__sigint_handler);
	sigaction(SIGINT, &sa, NULL);
}