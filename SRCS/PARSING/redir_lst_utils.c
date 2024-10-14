/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_lst_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: annabrag <annabrag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 20:30:40 by annabrag          #+#    #+#             */
/*   Updated: 2024/10/14 22:56:04 by annabrag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_ptrs(t_ptrs *p)
{
	p->new_task = NULL;
	p->i = 0;
	p->size = 0;
}

t_redir_lst	*redir_in_n_infile(t_data *d)
{
	t_redir_lst	*new_redir;

	new_redir = redir_lst_new_node(REDIR_IN);
	secure_malloc(new_redir);
	new_redir->infile = token_cleanup(d->token->next->content);
	return (new_redir);
}

t_redir_lst	*redir_out_trunc_n_outfile(t_data *d)
{
	t_redir_lst	*new_redir;

	new_redir = redir_lst_new_node(REDIR_OUT_TRUNC);
	secure_malloc(new_redir);
	new_redir->outfile = token_cleanup(d->token->next->content);
	return (new_redir);
}

t_redir_lst	*redir_out_append_n_outfile(t_data *d)
{
	t_redir_lst	*new_redir;

	new_redir = redir_lst_new_node(REDIR_OUT_APPEND);
	secure_malloc(new_redir);
	new_redir->outfile = token_cleanup(d->token->next->content);
	return (new_redir);
}

t_redir_lst	*heredoc_n_limiter(t_data *d)
{
	t_redir_lst	*new_redir;

	new_redir = redir_lst_new_node(HERE_DOC);
	secure_malloc(new_redir);
	new_redir->limiter = d->token->next->content;
	return (new_redir);
}
