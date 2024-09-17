/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage_collector.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: art3mis <art3mis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 15:33:03 by pmateo            #+#    #+#             */
/*   Updated: 2024/09/17 16:27:57 by art3mis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	*__create(t_gc_lst **yama, size_t size)
{
	void		*ptr;
	t_gc_lst	*node;

	ptr = malloc(size);
	if (ptr == NULL)
	{
		printf("ALLOCATION FAILED !\n");
		return (NULL);
	}
	node = new_gc_node(ptr);
	if (node == NULL)
	{
		printf("NODE CREATION FAILED !\n");
		return (NULL);
	}
	add_gc_node(yama, node);
	return (ptr);
}

static void	*__add(t_gc_lst **yama, void *ptr)
{
	t_gc_lst *node;

	node = new_gc_node(ptr);
	if (node == NULL)
	{
		printf("NODE CREATION FAILED !\n");
		return (NULL);
	}
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
		free((*yama)->ptr);
		(*yama)->ptr = NULL;
		free((*yama));
		(*yama) = tmp;
	}
	return (SUCCESS);
}

void	*yama(int flag, void *ptr, size_t size)
{
	static t_gc_lst *yama;

	if (flag == CREATE)
		ptr = __create(&yama, size);
	else if (flag == ADD)
		ptr = __add(&yama, ptr);
	else if (flag == REMOVE)
	{
		if (remove_gc_node(&yama, ptr) == FAILURE)
			printf("NO ALLOCATION FREED, YAMA IS EMPTY !\n");
		ptr = NULL;
	}
	else if (flag == CLEAN_ALL)
	{
		if (__clean_all(&yama) == FAILURE)
			printf("NO ALLOCATION FREED, YAMA IS EMPTY !\n");
		ptr = NULL;
	}
	else
	{
		printf("THIS YAMA'S FLAG DOESN'T EXIST !\n");
		ptr = NULL;
	}
	return (ptr);
}


//remplacer printf par ft_printf ou puterror lorsque yama aura ete teste