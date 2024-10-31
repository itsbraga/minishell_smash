/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_redir_lst.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: annabrag <annabrag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 20:44:31 by art3mis           #+#    #+#             */
/*   Updated: 2024/10/31 04:17:37 by annabrag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser_lexer.h"

static t_redir_lst	*__get_redir_infos(t_token_dblst *curr)
{
	t_redir_lst	*new_redir;

	new_redir = NULL;
	if (curr->next != NULL)
	{
		if (curr->type == REDIR_IN
			&& curr->next->type == INFILE)
			new_redir = redir_in_n_infile(curr);
		else if (curr->type == REDIR_OUT_TRUNC
			&& curr->next->type == OUTFILE)
			new_redir = redir_out_trunc_n_outfile(curr);
		else if (curr->type == REDIR_OUT_APPEND
			&& curr->next->type == OUTFILE)
			new_redir = redir_out_append_n_outfile(curr);
		else if (curr->type == HERE_DOC
			&& curr->next->type == LIMITER)
			new_redir = heredoc_n_limiter(curr);
	}
	return (new_redir);
}

static bool	__type_is_redir(t_token_type type)
{
	if (type == REDIR_IN || type == HERE_DOC || type == REDIR_OUT_TRUNC
		|| type == REDIR_OUT_APPEND)
		return (true);
	return (false);
}

int	create_redir_lst(t_data *d, t_exec_lst *existing_task)
{
	t_token_dblst	*curr;
	t_redir_lst		*new_redir;

	curr = d->token;
	new_redir = NULL;
	while (curr != NULL)
	{
		new_redir = __get_redir_infos(curr);
		if (__type_is_redir(curr->type) == false)
			curr = curr->next;
		else if (new_redir != NULL)
		{
			redir_lst_add_back(&(existing_task->redir), new_redir);
			curr = curr->next->next;
		}
	}
	return (ft_exit_status(SUCCESS, ADD));
}
