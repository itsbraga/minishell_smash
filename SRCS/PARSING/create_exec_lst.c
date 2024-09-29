/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_exec_lst.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: art3mis <art3mis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 17:44:18 by art3mis           #+#    #+#             */
/*   Updated: 2024/09/29 21:03:47 by art3mis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// appeler other_quotes (+ empty_quotes?)
// static char	*__quote_cleanup(t_token_dblst *t)
// {
// 	t_token_dblst	*head;
// 	char			*cleaned;

// 	head = t;
// 	while (head != NULL)
// 	{
		
// 	}
// 	return (cleaned);
// }

// manque absolute_path + bin_path

static int	__cmd_token_count(t_token_dblst *t)
{
	int	count;

	count = 0;
	while (t != NULL)
	{
		if (t->type == COMMAND || t->type == WORD)
			count++;
		t = t->next;
	}
	return (count);
}

int	create_exec_lst(t_data *d)
{
	t_exec_lst	*new_task;
	int			i;
	// char		*cleaned_token;

	if (d->token == NULL || d->token->content == NULL)
		return (FAILURE);
	if (d->exec == NULL)
	{
		d->exec = malloc(sizeof(t_exec_lst));
		secure_malloc(d->exec);
	}
	ft_bzero(d->exec, sizeof(t_exec_lst));
	while (d->token != NULL)
	{
		if (d->token->type == COMMAND)
		{
			i = 0;
			new_task = exec_lst_new_node();
			secure_malloc(new_task);
			new_task->cmd = yama(CREATE_TAB, NULL, (sizeof(char *) * (__cmd_token_count(d->token) + 1)));
			secure_malloc(new_task->cmd);
			new_task->cmd[i] = ft_strdup(d->token->content);
			printf(BP "node_cmd[0]:\t [" R "%s" BP "]\n" R, new_task->cmd[i]);
			i++;
			// (void)yama(ADD, new_task->cmd[i], 0);
		}
		else if (d->token->type == WORD)
		{
			i = 0;
			new_task->cmd[i] = ft_strdup(d->token->content);
			printf(BP "node_cmd[i]:\t [" R "%s" BP "]\n" R, new_task->cmd[i]);
			i++;
			// (void)yama(ADD, new_task->cmd[i], 0);
		}
		else if (d->token->type == HERE_DOC)
		{
			d->exec->heredoc_nb++;
			printf(ITAL "heredoc_nb: %d\n" R, d->exec->heredoc_nb);		
		}
		d->token = d->token->next;
		if (d->token == NULL)
		// {
		// 	new_task->cmd[i] = NULL;
			exec_lst_add_back(&(d->exec), new_task);
		// }
	}
	return (SUCCESS);
}
