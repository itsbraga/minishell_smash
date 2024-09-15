/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: art3mis <art3mis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 15:54:10 by pmateo            #+#    #+#             */
/*   Updated: 2024/09/15 22:09:13 by art3mis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gc.h"

int		remove_gc_node(t_gc_lst **yama, void *ptr)
{
	t_gc_lst *node;
	t_gc_lst *previous;
	
	if (yama == NULL || *yama == NULL)
		return (-1);
	if ((*yama)->ptr == ptr)
	{
		node = *yama;
		*yama = (*yama)->next;
		free(node->ptr);
		free(node);
		return (0);
	}
	previous = *yama;
	while (previous->next->ptr != ptr && previous->next != NULL)
		previous = previous->next;
	node = previous->next;
	previous->next = (previous->next)->next;
	free(node->ptr);
	free(node);
	return (0);
}

void	add_gc_node(t_gc_lst **yama, t_gc_lst *node)
{
	t_gc_lst *tmp;

	if (*yama == NULL)
		*yama = node;
	else
	{
		tmp = last_gc_lst_node(*yama);
		tmp->next = node;
	}
}

t_gc_lst	*last_gc_lst_node(t_gc_lst *yama)
{
	if (yama == NULL)
		return (NULL);
	else
	{
		while (yama->next != NULL)
			yama = yama->next;
		return (yama);
	}
}

void	*new_gc_node(void *ptr)
{
	t_gc_lst	*node;

	node = malloc(sizeof(t_gc_lst));
	if (node == NULL)
		return (NULL);
	node->ptr = ptr;
	node->next = NULL;
	return (node);
}