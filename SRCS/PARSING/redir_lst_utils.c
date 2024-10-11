/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_lst_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: art3mis <art3mis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 20:30:40 by annabrag          #+#    #+#             */
/*   Updated: 2024/10/11 22:24:03 by art3mis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_redir_lst	*redir_in_n_infile(t_data *d)
{
	t_redir_lst *new_redir;

	new_redir = redir_lst_new_node(REDIR_IN);
	secure_malloc(new_redir);
	new_redir->infile = token_cleanup(d->token->next->content);
	printf(BOLD PURPLE "new_redir:\t [" R "%d" BOLD PURPLE "]\n" R, new_redir->type);
	printf(PURPLE "infile:\t\t [" R "%s" PURPLE "]\n" R, new_redir->infile);
	return (new_redir);
}

t_redir_lst *redir_out_trunc_n_outfile(t_data *d)
{
	t_redir_lst *new_redir;

	new_redir = redir_lst_new_node(REDIR_OUT_TRUNC);
	secure_malloc(new_redir);
	new_redir->outfile = token_cleanup(d->token->next->content);
	printf(BOLD PURPLE "new_redir:\t [" R "%d" BOLD PURPLE "]\n" R, new_redir->type);
	printf(PURPLE "outfile:\t [" R "%s" PURPLE "]\n" R, new_redir->outfile);
	return (new_redir);
}

t_redir_lst *redir_out_append_n_outfile(t_data *d)
{
	t_redir_lst *new_redir;

	new_redir = redir_lst_new_node(REDIR_OUT_APPEND);
	secure_malloc(new_redir);
	new_redir->outfile = token_cleanup(d->token->next->content);
	printf(BOLD PURPLE "new_redir:\t [" R "%d" BOLD PURPLE "]\n" R, new_redir->type);
	printf(PURPLE "outfile:\t [" R "%s" PURPLE "]\n" R, new_redir->outfile);
	return (new_redir);
}

t_redir_lst *heredoc_n_limiter(t_data *d)
{
	t_redir_lst *new_redir;

	d->exec->heredoc_nb++;
	new_redir = redir_lst_new_node(HERE_DOC);
	secure_malloc(new_redir);
	new_redir->limiter = d->token->next->content;
	printf(BOLD PURPLE "new_redir:\t [" R "%d" BOLD PURPLE "]\n" R, new_redir->type);
	printf(PURPLE "limiter:\t [" R "%s" PURPLE "]\n" R, new_redir->limiter);
	return (new_redir);
}
