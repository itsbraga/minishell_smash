/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_lst.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: annabrag <annabrag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 01:00:46 by art3mis           #+#    #+#             */
/*   Updated: 2024/10/31 11:24:21 by annabrag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tools.h"

t_exec_lst	*exec_lst_new_node(void)
{
	t_exec_lst	*new_node;

	new_node = malloc(sizeof(t_exec_lst));
	secure_malloc(new_node, true);
	new_node->redir = NULL;
	new_node->heredoc_nb = 0;
	new_node->latest_hd = 0;
	new_node->is_given_path = false;
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
	t_exec_lst	*curr;

	size = 0;
	curr = *e;
	while (curr != NULL)
	{
		size++;
		curr = curr->next;
	}
	return (size);
}
