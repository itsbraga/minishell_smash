/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_lst_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: art3mis <art3mis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 20:30:40 by annabrag          #+#    #+#             */
/*   Updated: 2024/10/21 01:08:55 by art3mis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_redir_lst	*redir_in_n_infile(t_data *d)
{
	t_redir_lst	*new_redir;

	new_redir = redir_lst_new_node(REDIR_IN);
	secure_malloc(new_redir, true);
	new_redir->infile = token_cleanup(d->token->next->content);
	return (new_redir);
}

t_redir_lst	*redir_out_trunc_n_outfile(t_data *d)
{
	t_redir_lst	*new_redir;

	new_redir = redir_lst_new_node(REDIR_OUT_TRUNC);
	secure_malloc(new_redir, true);
	new_redir->outfile = token_cleanup(d->token->next->content);
	return (new_redir);
}

t_redir_lst	*redir_out_append_n_outfile(t_data *d)
{
	t_redir_lst	*new_redir;

	new_redir = redir_lst_new_node(REDIR_OUT_APPEND);
	secure_malloc(new_redir, true);
	new_redir->outfile = token_cleanup(d->token->next->content);
	return (new_redir);
}

t_redir_lst	*heredoc_n_limiter(t_data *d)
{
	t_redir_lst	*new_redir;

	new_redir = redir_lst_new_node(HERE_DOC);
	secure_malloc(new_redir, true);
	new_redir->limiter = d->token->next->content;
	return (new_redir);
}
