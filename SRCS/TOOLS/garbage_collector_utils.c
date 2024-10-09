/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage_collector_utils.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: annabrag <annabrag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 15:54:10 by pmateo            #+#    #+#             */
/*   Updated: 2024/10/09 21:33:42 by annabrag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	*new_gc_node(void *ptr, bool is_tab)
{
	t_gc_lst	*node;

	node = malloc(sizeof(t_gc_lst));
	secure_malloc(node);
	node->ptr = ptr;
	node->is_tab = is_tab;
	node->next = NULL;
	return (node);
}

void	add_gc_node(t_gc_lst **yama, t_gc_lst *node)
{
	t_gc_lst	*tmp;

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
		if (node->is_tab == true)
			free_tab((char **)node->ptr);
		else
			free(node->ptr);
		free(node);
		return (SUCCESS);
	}
	prev = *yama;
	while (prev->next->ptr != ptr && prev->next != NULL)
		prev = prev->next;
	node = prev->next;
	prev->next = (prev->next)->next;
	free(node->ptr);
	free(node);
	return (SUCCESS);
}

void	free_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i] != NULL)
	{
		free(tab[i]);
		tab[i] = NULL;
		i++;
	}
	free(tab);
	tab = NULL;
}
