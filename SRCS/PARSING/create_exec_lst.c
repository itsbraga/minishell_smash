/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_exec_lst.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: art3mis <art3mis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 17:44:18 by art3mis           #+#    #+#             */
/*   Updated: 2024/09/27 02:44:20 by art3mis          ###   ########.fr       */
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

static void	__secure_malloc(t_exec_lst *new_task)
{
	if (new_task == NULL)
	{
		err_msg("malloc", ERR_MALLOC, 0);
		clean_exit_shell(FAILURE);
	}
}

// // manque absolute_path + bin_path
int	create_exec_lst(t_data *d)
{
	t_exec_lst	*new_task;
	int			i;
	// char		*cleaned_token;

	if (d->main == NULL || d->main->content == NULL)
		return (FAILURE);
	while (d->main != NULL)
	{
		i = 0;
		if (d->token->type == COMMAND)
		{
			new_task = exec_lst_new_node(d);
			__secure_malloc(new_task);
			new_task->cmd[0] = d->token->content;
		}
		if (d->token->type == WORD)
		{
			new_task = exec_lst_new_node(d);
			__secure_malloc(new_task);
			new_task->cmd[i] = d->token->content;
		}
		exec_lst_add_back(&(d->exec), new_task);
		i++;
		d->main = d->main->next;
	}
	return (SUCCESS);
}
