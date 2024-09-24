/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_redir_lst.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: art3mis <art3mis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 20:44:31 by art3mis           #+#    #+#             */
/*   Updated: 2024/09/24 22:25:14 by art3mis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	fill_redir_lst(t_token_dblst *t, t_redir_lst **r_head)
{
	t_redir_lst	*new_redir;

	while (t != NULL)
	{
		if (t->type == REDIR_IN && t->next != NULL && t->next->type == INFILE)
		{
			new_redir = redir_lst_new_node(REDIR_IN);
			printf(GREEN "new_redir:\t [" R "%d" GREEN "]\n" R, new_redir->type);
			new_redir->infile = t->next->content;
			printf(GREEN "infile:\t\t [" R "%s" GREEN "]\n" R, new_redir->infile);
		}
		else if (t->type == HERE_DOC && t->next != NULL && t->next->type == LIMITER)
		{
			new_redir = redir_lst_new_node(HERE_DOC);
			printf(GREEN "new_redir:\t [" R "%d" GREEN "]\n" R, new_redir->type);
			new_redir->limiter = t->next->content;
			printf(GREEN "limiter:\t [" R "%s" GREEN "]\n" R, new_redir->limiter);
		}
		else if (t->type == REDIR_OUT_TRUNC && t->next != NULL && t->next->type == OUTFILE)
		{
			new_redir = redir_lst_new_node(REDIR_OUT_TRUNC);
			printf(GREEN "new_redir:\t [" R "%d" GREEN "]\n" R, new_redir->type);
			new_redir->outfile = t->next->content;
			printf(GREEN "trunc_outfile:\t [" R "%s" GREEN "]\n" R, new_redir->outfile);
		}
		else if (t->type == REDIR_OUT_APPEND && t->next != NULL && t->next->type == OUTFILE)
		{
			new_redir = redir_lst_new_node(REDIR_OUT_APPEND);
			printf(GREEN "new_redir:\t [" R "%d" GREEN "]\n" R, new_redir->type);
			new_redir->outfile = t->next->content;
			printf(GREEN "append_outfile:\t [" R "%s" GREEN "]\n" R, new_redir->outfile);
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
