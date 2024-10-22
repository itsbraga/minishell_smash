/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage_collector.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: art3mis <art3mis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 15:33:03 by pmateo            #+#    #+#             */
/*   Updated: 2024/10/22 23:32:12 by art3mis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tools.h"

static void	*__create(t_gc_lst **yama, size_t size, bool is_tab)
{
	void		*ptr;
	t_gc_lst	*node;

	ptr = malloc(size);
	if (ptr == NULL)
	{
		err_msg(NULL, ERR_MALLOC, 0);
		return (NULL);
	}
	node = new_gc_node(ptr, is_tab);
	if (node == NULL)
	{
		err_msg(NULL, ERR_MALLOC, 0);
		return (NULL);
	}
	add_gc_node(yama, node);
	return (ptr);
}

static void	*__add(t_gc_lst **yama, void *ptr, bool is_tab)
{
	t_gc_lst	*node;

	node = new_gc_node(ptr, is_tab);
	if (node == NULL)
	{
		err_msg(NULL, ERR_MALLOC, 0);
		return (NULL);
	}
	add_gc_node(yama, node);
	return (ptr);
}

static int	__handle_remove(t_gc_lst **yama, void *ptr)
{
	t_gc_lst	*node;

	node = *yama;
	while (node->ptr != ptr)
		node = node->next;
	if (node->is_tab == true)
		return (free_gc_tab(yama, node->ptr));
	else
		return (remove_gc_node(yama, ptr));
}

static int	__clean_all(t_gc_lst **yama)
{
	t_gc_lst	*tmp;

	if (yama == NULL || *yama == NULL)
		return (FAILURE);
	while ((*yama) != NULL)
	{
		tmp = (*yama)->next;
		(*yama)->next = NULL;
		free_and_set_null((*yama)->ptr);
		free_and_set_null((*yama));
		// free((*yama));
		(*yama) = tmp;
	}
	return (SUCCESS);
}

void	*yama(int flag, void *ptr, size_t size)
{
	static t_gc_lst	*yama;

	if (flag == CREATE)
		return (__create(&yama, size, false));
	else if (flag == CREATE_TAB)
		return (__create(&yama, size, true));
	else if (flag == ADD)
		return (__add(&yama, ptr, false));
	else if (flag == ADD_TAB)
		return (__add(&yama, ptr, true));
	else if (flag == REMOVE)
	{
		if (__handle_remove(&yama, ptr) == FAILURE)
			err_msg(NULL, "No allocation freed, Yama is empty", 0);
		return (NULL);
	}
	else if (flag == CLEAN_ALL)
	{
		if (__clean_all(&yama) == FAILURE)
			err_msg(NULL, "No allocation freed, Yama is empty", 0);
		return (NULL);
	}
	else
		return (err_msg(NULL, "This Yama flag doesn't exist", 0), NULL);
}
