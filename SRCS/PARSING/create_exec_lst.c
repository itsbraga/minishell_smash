/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_exec_lst.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: art3mis <art3mis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 17:44:18 by art3mis           #+#    #+#             */
/*   Updated: 2024/09/27 01:52:00 by art3mis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

typedef struct s_exec_lst
{
	t_redir_lst			*redir;			// est cree dans create_token_dblst.c
	int					heredoc_nb;		// s'incremente dans identify_token.c
	bool				absolute_path;
	char				*bin_path;
	char				**cmd;
	struct s_exec_lst	*next;
}				t_exec_lst;

static void	__quote_cleanup(t_token_dblst *t)
{
	t_token_dblst	*tmp;

	tmp = t;
	while (tmp != NULL)
	{
		
	}
}

static void	__secure_malloc(t_exec_lst *new_task)
{
	if (new_task == NULL)
	{
		err_msg("malloc", ERR_MALLOC, 0);
		clean_exit_shell(FAILURE);
	}
}

// passer other_quotes() sur les COMMAND, INFILE, OUTFILE, LIMITER mais pas WORD
//
// manque absolute_path + bin_path
t_exec_lst	create_exec_lst(t_data *d)
{
	t_exec_lst	*new_task;
	char		*cleaned_token;

	while (d->main != NULL)
	{
		if (d->token->type == COMMAND)
		{
			new_task = exec_lst_new_node(d->token);
			__secure_malloc(new_task);
			new_task->cmd[0] = d->token->content;
		}
		if (d->token->type == WORD)
		{
			new_task = exec_lst_new_node(d->token);
			__secure_malloc(new_task);
			new_task->cmd = d->token->content;
		}
		exec_lst_add_back(&(d->exec), new_task);
		d->main = d->main->next;
	}
}
