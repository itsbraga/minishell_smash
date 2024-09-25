/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_redir_lst.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: annabrag <annabrag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 20:44:31 by art3mis           #+#    #+#             */
/*   Updated: 2024/09/25 20:04:22 by annabrag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	__redir_in_and_out(t_token_dblst *t)
{
	t_redir_lst	*new_redir;

	if (t->next != NULL)
	{
		if (t->type == REDIR_IN && t->next->type == INFILE)
		{
			new_redir = redir_lst_new_node(REDIR_IN);
			// printf(BOLD PINK "new_redir:\t [" R "%d" BOLD PINK "]\n" R, new_redir->type);
			new_redir->infile = t->next->content;
			// printf(BOLD PINK "infile:\t\t [" R "%s" BOLD PINK "]\n" R, new_redir->infile);
		}
		else if (t->type == REDIR_OUT_TRUNC && t->next->type == OUTFILE)
		{
			new_redir = redir_lst_new_node(REDIR_OUT_TRUNC);
			// printf(BOLD PINK "new_redir:\t [" R "%d" BOLD PINK "]\n" R, new_redir->type);
			new_redir->outfile = t->next->content;
			// printf(BOLD PINK "trunc_outfile:\t [" R "%s" BOLD PINK "]\n" R, new_redir->outfile);
		}
		else if (t->type == REDIR_OUT_APPEND && t->next->type == OUTFILE)
		{
			new_redir = redir_lst_new_node(REDIR_OUT_APPEND);
			// printf(BOLD PINK "new_redir:\t [" R "%d" BOLD PINK "]\n" R, new_redir->type);
			new_redir->outfile = t->next->content;
			// printf(BOLD PINK "append_outfile:\t [" R "%s" BOLD PINK "]\n" R, new_redir->outfile);
		}
	}
}

void	fill_redir_lst(t_token_dblst *t, t_redir_lst **r_head)
{
	t_redir_lst	*new_redir;

	lstclear_redir(r_head);
	while (t != NULL)
	{
		__redir_in_and_out(t);
		if (t->type == HERE_DOC && t->next != NULL && t->next->type == LIMITER)
		{
			new_redir = redir_lst_new_node(HERE_DOC);
			// printf(BOLD PINK "new_redir:\t [" R "%d" BOLD PINK "]\n" R, new_redir->type);
			new_redir->limiter = t->next->content;
			// printf(BOLD PINK "limiter:\t [" R "%s" BOLD PINK "]\n" R, new_redir->limiter);
		}
		else
		{
			t = t->next;
			continue;
		}
		redir_lst_add_back(r_head, new_redir);
		t = t->next->next; // eviter de traiter deux fois redir + file/lim
	}
}
