/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage_collector_utils.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: annabrag <annabrag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 15:54:10 by pmateo            #+#    #+#             */
/*   Updated: 2024/09/16 20:03:20 by annabrag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	remove_gc_node(t_gc_lst **yama, void *ptr)
{
	t_gc_lst *node;
	t_gc_lst *prev;
	
	if (yama == NULL || *yama == NULL)
		return (-1);
	if ((*yama)->ptr == ptr)
	{
		node = *yama;
		*yama = (*yama)->next;
		free(node->ptr);
		free(node);
		return (EXIT_SUCCESS);
	}
	prev = *yama;
	while (prev->next->ptr != ptr && prev->next != NULL)
		prev = prev->next;
	node = prev->next;
	prev->next = (prev->next)->next;
	free(node->ptr);
	free(node);
	return (EXIT_SUCCESS);
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