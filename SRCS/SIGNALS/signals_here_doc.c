/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals_here_doc.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: art3mis <art3mis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 21:53:48 by art3mis           #+#    #+#             */
/*   Updated: 2024/10/22 23:51:34 by art3mis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void __sigint_handler_heredoc(int sig)
{
	t_data	*d;

	(void)sig;
	d = data_struct();
	ft_putchar_fd('\n', STDOUT_FILENO);
    // fonction pour fermer le fd
	g_sig_code = 1;
	d->last_exit_status = 130;
}

// appeler cet handler dans la fonction d'ouverture d'here_doc
void    set_signals_in_heredoc(void)
{
	signal(SIGINT, &__sigint_handler_heredoc);
	signal(SIGQUIT, SIG_IGN);
}
