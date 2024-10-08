/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage_collector.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: annabrag <annabrag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 15:33:03 by pmateo            #+#    #+#             */
/*   Updated: 2024/10/08 17:03:06 by annabrag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	*__create(t_gc_lst **yama, size_t size, bool is_tab)
{
	void		*ptr;
	t_gc_lst	*node;

	ptr = malloc(size);
	secure_malloc(ptr);
	if (ptr == NULL)
		return (err_msg(NULL, ERR_MALLOC, 0), NULL);
	node = new_gc_node(ptr, is_tab);
	secure_malloc(node);
	if (node == NULL)
		return (err_msg(NULL, ERR_MALLOC, 0), NULL);
	add_gc_node(yama, node);
	return (ptr);
}

static void	*__add(t_gc_lst **yama, void *ptr, bool is_tab)
{
	t_gc_lst *node;

	node = new_gc_node(ptr, is_tab);
	secure_malloc(node);
	if (node == NULL)
		return (err_msg(NULL, ERR_MALLOC, 0), NULL);
	add_gc_node(yama, node);
	return (ptr);
}

static int	__clean_all(t_gc_lst **yama)
{
	t_gc_lst *tmp;

	if (yama == NULL || *yama == NULL)
		return (FAILURE);
	while ((*yama) != NULL)
	{
		tmp = (*yama)->next;
		(*yama)->next = NULL;
		if ((*yama)->is_tab == true)
			free_tab((char **)(*yama)->ptr);
		else
		{
			free((*yama)->ptr);
			(*yama)->ptr = NULL;
		}
		free((*yama));
		(*yama) = tmp;
	}
	return (SUCCESS);
}

void	*yama(int flag, void *ptr, size_t size)
{
	static t_gc_lst *yama;

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
		if (remove_gc_node(&yama, ptr) == FAILURE)
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
