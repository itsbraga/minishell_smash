/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_exec_lst.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: art3mis <art3mis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 17:44:18 by art3mis           #+#    #+#             */
/*   Updated: 2024/09/28 00:58:51 by art3mis          ###   ########.fr       */
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
		printf("Token type: %d, content: %s\n", t->type, t->content);
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
	while (d->token != NULL)
	{
		if (d->token->type == COMMAND)
		{
			i = 0;
			new_task = exec_lst_new_node();
			printf(RED "new_task: %p\n" R, new_task);
			secure_malloc(new_task);
			// new_task->cmd = yama(CREATE_TAB, NULL, (sizeof(char *) * (__cmd_token_count(d->token) + 1)));
			new_task->cmd = malloc(sizeof(char *) * (__cmd_token_count(d->token) + 1));
			secure_malloc(new_task->cmd);
			printf(RED "i: %d, token content: %s\n" R, i, d->token->content);
			new_task->cmd[i] = ft_strdup(d->token->content);
			printf(BP "node_cmd[0]:\t [" R "%s" BP "]\n" R, new_task->cmd[0]);
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
			new_task->heredoc_nb++;
			printf(ITAL "\nheredoc_nb: %d\n\n" R, new_task->heredoc_nb);		
		}
		d->token = d->token->next;
		if (d->token == NULL)
		{
			new_task->cmd[i] = NULL;
			exec_lst_add_back(&(d->exec), new_task);
		}
	}
	return (SUCCESS);
}
