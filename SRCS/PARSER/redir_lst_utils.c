/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_lst_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: annabrag <annabrag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 20:30:40 by annabrag          #+#    #+#             */
/*   Updated: 2024/10/31 04:17:37 by annabrag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser_lexer.h"

t_redir_lst	*redir_in_n_infile(t_token_dblst *curr)
{
	t_redir_lst	*new_redir;

	new_redir = redir_lst_new_node(REDIR_IN);
	secure_malloc(new_redir, true);
	new_redir->infile = token_cleanup(ft_strdup(curr->next->content));
	return (new_redir);
}

t_redir_lst	*redir_out_trunc_n_outfile(t_token_dblst *curr)
{
	t_redir_lst	*new_redir;

	new_redir = redir_lst_new_node(REDIR_OUT_TRUNC);
	secure_malloc(new_redir, true);
	new_redir->outfile = token_cleanup(ft_strdup(curr->next->content));
	return (new_redir);
}

t_redir_lst	*redir_out_append_n_outfile(t_token_dblst *curr)
{
	t_redir_lst	*new_redir;

	new_redir = redir_lst_new_node(REDIR_OUT_APPEND);
	secure_malloc(new_redir, true);
	new_redir->outfile = token_cleanup(ft_strdup(curr->next->content));
	return (new_redir);
}

t_redir_lst	*heredoc_n_limiter(t_token_dblst *curr)
{
	t_redir_lst	*new_redir;

	new_redir = redir_lst_new_node(HERE_DOC);
	secure_malloc(new_redir, true);
	new_redir->limiter = ft_strdup(curr->next->content);
	return (new_redir);
}
