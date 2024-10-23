/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_redir_lst.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: annabrag <annabrag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 20:44:31 by art3mis           #+#    #+#             */
/*   Updated: 2024/10/23 15:14:37 by annabrag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing-lexing.h"

static t_redir_lst	*__get_redir_infos(t_token_dblst *current)
{
	t_redir_lst	*new_redir;

	new_redir = NULL;
	if (current->next != NULL)
	{
		if (current->type == REDIR_IN
			&& current->next->type == INFILE)
			new_redir = redir_in_n_infile(current);
		else if (current->type == REDIR_OUT_TRUNC
			&& current->next->type == OUTFILE)
			new_redir = redir_out_trunc_n_outfile(current);
		else if (current->type == REDIR_OUT_APPEND
			&& current->next->type == OUTFILE)
			new_redir = redir_out_append_n_outfile(current);
		else if (current->type == HERE_DOC
			&& current->next->type == LIMITER)
			new_redir = heredoc_n_limiter(current);
	}
	return (new_redir);
}

int	create_redir_lst(t_data *d, t_exec_lst *existing_task)
{
	t_token_dblst	*current;
	t_redir_lst		*new_redir;

	current = d->token;
	new_redir = NULL;
	while (current != NULL)
	{
		new_redir = __get_redir_infos(current);
		if (IS_REDIR(current->type) == false)
			current = current->next;
		else if (new_redir != NULL)
		{
			redir_lst_add_back(&(existing_task->redir), new_redir);
			current = current->next->next;
		}
	}
	return (SUCCESS);
}
