/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_redir_lst2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: art3mis <art3mis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 20:44:31 by art3mis           #+#    #+#             */
/*   Updated: 2024/10/12 01:45:51 by art3mis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_redir_lst	*__get_redir_infos(t_data *d)
{
	t_redir_lst *new_redir;

	if (d->token->next != NULL)
	{
		if (d->token->type == REDIR_IN
			&& d->token->next->type == INFILE)
			new_redir = redir_in_n_infile(d);
		else if (d->token->type == REDIR_OUT_TRUNC
			&& d->token->next->type == OUTFILE)
			new_redir = redir_out_trunc_n_outfile(d);
		else if (d->token->type == REDIR_OUT_APPEND
			&& d->token->next->type == OUTFILE)
			new_redir = redir_out_append_n_outfile(d);
		else if (d->token->type == HERE_DOC
			&& d->token->next->type == LIMITER)
			new_redir = heredoc_n_limiter(d);
	}
	return (new_redir);
}

int	create_redir_lst2(t_data *d, t_exec_lst *existing_task)
{
	t_redir_lst		*new_redir;

	lstclear_redir(&(d->exec->redir));
	printf("--------------------------------- d->exec->redir -------------------------------\n");
	while (d->token != NULL)
	{
		new_redir = __get_redir_infos(d);
		if (IS_REDIR(d->token->type) == false)
			d->token = d->token->next;
		else if (new_redir != NULL)
		{
			redir_lst_add_back(&(existing_task->redir), new_redir);
			d->token = d->token->next->next;
		}
	}
	// display_redir_lst(d->exec->redir);
	return (SUCCESS);
}
