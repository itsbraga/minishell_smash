/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals_here_doc.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: art3mis <art3mis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 22:39:40 by art3mis           #+#    #+#             */
/*   Updated: 2024/10/21 22:57:44 by art3mis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void __sigint_handler_heredoc(int sig)
{
	(void)sig;
	ft_putchar_fd('\n', STDOUT_FILENO);
    // fonction pour fermer le fd
	g_sig_code = 2; // verifier
}

// appeler cet handler dans la fonction d'ouverture d'here_doc
void    set_signals_in_heredoc(void)
{
    struct sigaction	sa;

	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sa.sa_handler = __sigint_handler_heredoc;
	sigaction(SIGINT, &sa, NULL);
	handle_sigquit();
}
