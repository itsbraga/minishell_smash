/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage_collector.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: art3mis <art3mis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 15:33:03 by pmateo            #+#    #+#             */
/*   Updated: 2024/11/02 03:06:40 by art3mis          ###   ########.fr       */
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

static	void	*__add_tab(t_gc_lst **yama, void *ptr)
{
	int			i;
	char		**tab;
	t_gc_lst	*node;

	i = 0;
	tab = (char **)ptr;
	node = new_gc_node(tab, true);
	if (node == NULL)
		return (err_msg(NULL, ERR_MALLOC, 0), NULL);
	add_gc_node(yama, node);
	while (tab[i] != NULL)
	{
		node = new_gc_node(tab[i], false);
		if (node == NULL)
			return (err_msg(NULL, ERR_MALLOC, 0), NULL);
		add_gc_node(yama, node);
		i++;
	}
	return (ptr);
}

static void	*__add(t_gc_lst **yama, void *ptr, bool is_tab)
{
	t_gc_lst	*node;

	if (is_tab == true)
		return (__add_tab(yama, ptr));
	node = new_gc_node(ptr, is_tab);
	if (node == NULL)
	{
		err_msg(NULL, ERR_MALLOC, 0);
		return (NULL);
	}
	add_gc_node(yama, node);
	return (ptr);
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
		free_and_set_null((void **)&(*yama)->ptr);
		free((*yama));
		(*yama) = tmp;
	}
	return (SUCCESS);
}

void	*yama(int flag, void *ptr, size_t size)
{
	static t_gc_lst	*yama;

	if (flag == SEARCH)
		return (search_ptr(&yama, ptr));
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
		if (handle_remove(&yama, ptr) == FAILURE)
			err_msg(NULL, "No allocation freed, Yama is empty", 0);
		return (NULL);
	}
	else if (flag == CLEAN_ALL)
	{
		if (__clean_all(&yama) == FAILURE)
			err_msg(NULL, "No allocation freed, Yama is empty", 0);
		return (NULL);
	}
	return (err_msg(NULL, "This Yama flag doesn't exist", 0), NULL);
}
