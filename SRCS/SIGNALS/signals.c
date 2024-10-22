/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: art3mis <art3mis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 19:19:11 by annabrag          #+#    #+#             */
/*   Updated: 2024/10/22 22:48:23 by art3mis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	__rl_reset_custom_prompt(void)
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
	t_data	*d;

	(void)signo;
	d = data_struct();
	ft_putchar_fd('\n', STDOUT_FILENO);
	g_sig_code = 1;
	d->last_exit_status = 130;
	__rl_reset_custom_prompt();
}

void	set_signals(void)
{
	signal(SIGINT, &__sigint_handler);
	signal(SIGQUIT, SIG_IGN);
}
