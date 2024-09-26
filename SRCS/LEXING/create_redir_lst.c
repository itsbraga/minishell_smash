/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_redir_lst.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: art3mis <art3mis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 20:44:31 by art3mis           #+#    #+#             */
/*   Updated: 2024/09/27 01:38:05 by art3mis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	__secure_malloc(t_redir_lst *new_redir)
{
	if (new_redir == NULL)
	{
		err_msg("malloc", ERR_MALLOC, 0);
		clean_exit_shell(FAILURE);
	}
}

static void	__redir_in_and_out(t_token_dblst *t)
{
	t_redir_lst	*new_redir;

	if (t->next != NULL)
	{
		if (t->type == REDIR_IN && t->next->type == INFILE)
		{
			new_redir = redir_lst_new_node(REDIR_IN);
			__secure_malloc(new_redir);
			new_redir->infile = t->next->content;
		}
		else if (t->type == REDIR_OUT_TRUNC && t->next->type == OUTFILE)
		{
			new_redir = redir_lst_new_node(REDIR_OUT_TRUNC);
			__secure_malloc(new_redir);
			new_redir->outfile = t->next->content;
		}
		else if (t->type == REDIR_OUT_APPEND && t->next->type == OUTFILE)
		{
			new_redir = redir_lst_new_node(REDIR_OUT_APPEND);
			__secure_malloc(new_redir);
			new_redir->outfile = t->next->content;
		}
	}
}
/*
			printf(BOLD PINK "new_redir:\t [" R "%d" BOLD PINK "]\n" R, new_redir->type);
			printf(BOLD PINK "infile:\t\t [" R "%s" BOLD PINK "]\n" R, new_redir->infile);

			printf(BOLD PINK "new_redir:\t [" R "%d" BOLD PINK "]\n" R, new_redir->type);
			printf(BOLD PINK "outfile:\t [" R "%s" BOLD PINK "]\n" R, new_redir->outfile);

			printf(BOLD PINK "new_redir:\t [" R "%d" BOLD PINK "]\n" R, new_redir->type);
			printf(BOLD PINK "outfile:\t [" R "%s" BOLD PINK "]\n" R, new_redir->outfile);

			printf(BOLD PINK "new_redir:\t [" R "%d" BOLD PINK "]\n" R, new_redir->type);
			printf(BOLD PINK "limiter:\t [" R "%s" BOLD PINK "]\n" R, new_redir->limiter);
*/

void	create_redir_lst(t_redir_lst **r_head, t_token_dblst *t)
{
	t_redir_lst	*new_redir;

	lstclear_redir(r_head);
	while (t != NULL)
	{
		__redir_in_and_out(t);
		if (t->type == HERE_DOC && t->next != NULL && t->next->type == LIMITER)
		{
			new_redir = redir_lst_new_node(HERE_DOC);
			__secure_malloc(new_redir);
			new_redir->limiter = t->next->content;
		}
		else
		{
			t = t->next;
			continue ;
		}
		redir_lst_add_back(r_head, new_redir);
		t = t->next->next; // eviter de traiter deux fois redir + file/lim
	}
}
