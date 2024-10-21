/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage_collector_utils.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmateo <pmateo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 15:54:10 by pmateo            #+#    #+#             */
/*   Updated: 2024/10/21 20:09:27 by pmateo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	*new_gc_node(void *ptr, bool is_tab)
{
	t_gc_lst	*node;

	node = malloc(sizeof(t_gc_lst));
	if (node == NULL)
		return (err_msg(NULL, ERR_MALLOC, 0), NULL);
	node->ptr = ptr;
	node->is_tab = is_tab;
	node->next = NULL;
	return (node);
}

static t_gc_lst	*__last_gc_lst_node(t_gc_lst *yama)
{
	if (yama == NULL)
		return (NULL);
	while (yama->next != NULL)
		yama = yama->next;
	return (yama);
}

void	add_gc_node(t_gc_lst **yama, t_gc_lst *node)
{
	t_gc_lst	*tmp;

	if (*yama == NULL)
		*yama = node;
	else
	{
		tmp = __last_gc_lst_node(*yama);
		tmp->next = node;
	}
}

int	remove_gc_node(t_gc_lst **yama, void *ptr)
{
	t_gc_lst	*node;
	t_gc_lst	*prev;

	if (yama == NULL || *yama == NULL)
		return (FAILURE);
	if ((*yama)->ptr == ptr)
	{
		node = *yama;
		*yama = (*yama)->next;
		free(node->ptr);
		node->ptr = NULL;
		free(node);
		return (SUCCESS);
	}
	prev = *yama;
	while (prev->next != NULL && prev->next->ptr != ptr)
		prev = prev->next;
	node = prev->next;
	prev->next = (prev->next)->next;
	free(node->ptr);
	node->ptr = NULL;
	free(node);
	return (SUCCESS);
}

int	free_gc_tab(t_gc_lst **yama, char **tab)
{
	int	error;
	int	i;

	error = 0;
	i = 0;
	while (tab[i] != NULL)
	{
		error = remove_gc_node(yama, tab[i]);
		i++;
	}
	remove_gc_node(yama, tab);
	return (error);
}
