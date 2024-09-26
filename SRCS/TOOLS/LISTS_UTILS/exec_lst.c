/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_lst.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: art3mis <art3mis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 01:00:46 by art3mis           #+#    #+#             */
/*   Updated: 2024/09/27 01:50:01 by art3mis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_exec_lst *exec_lst_new_node(t_token_dblst *t)
{
	t_exec_lst	*new_node;
	
	new_node = yama(CREATE, NULL, sizeof(t_exec_lst));
	if (new_node == NULL)
	{
		err_msg("malloc", ERR_MALLOC, 0);
		clean_exit_shell(FAILURE);
	}
	new_node->redir = NULL;
	new_node->heredoc_nb = t->exec->heredoc_nb;
	new_node->absolute_path = false;
	new_node->bin_path = NULL;
	new_node->cmd = NULL;
	new_node->next = NULL;
	return (new_node);
}

static t_exec_lst	*__exec_lst_last_node(t_exec_lst *e)
{
	if (e == NULL)
		return (NULL);
	while (e->next != NULL)
		e = e->next;
	return (e);
}

void	exec_lst_add_back(t_exec_lst **e, t_exec_lst *new_node)
{
	t_exec_lst	*tmp;

	if (e == NULL)
		return ;
	if ((*e) == NULL)
		*e = new_node;
	else
	{
		tmp = __exec_lst_last_node(*e);
		tmp->next = new_node;
	}
}

size_t	get_exec_lst_size(t_exec_lst **e)
{
	size_t		size;
	t_exec_lst	*node;

	size = 0;
	node = *e;
	while (node != NULL)
	{
		size++;
		node = node->next;
	}
	return (size);
}
