/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage_collector.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: annabrag <annabrag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 15:33:03 by pmateo            #+#    #+#             */
/*   Updated: 2024/09/16 20:03:26 by annabrag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	*create(t_gc_lst **yama, size_t	size)
{
	void		*ptr;
	t_gc_lst	*node;

	ptr = malloc(size);
	if (ptr == NULL)
		return (printf("ALLOCATION FAILED !\n"), NULL);
	node = new_gc_node(ptr);
	if (node == NULL)
		return (printf("NODE CREATION FAILED !\n"), NULL);
	add_gc_node(yama, node);
	return (ptr);
}

void	*add(t_gc_lst **yama, void *ptr)
{
	t_gc_lst *node;

	node = new_gc_node(ptr);
	if (node == NULL)
		return (printf("NODE CREATION FAILED !\n"), NULL);
	add_gc_node(yama, node);
	return (ptr);
}

int	clean_all(t_gc_lst **yama)
{
	t_gc_lst *tmp;

	if (yama == NULL || *yama == NULL)
		return (-1);
	while ((*yama) != NULL)
	{
		tmp = (*yama)->next;
		(*yama)->next = NULL;
		free((*yama)->ptr);
		(*yama)->ptr = NULL;
		free((*yama));
		(*yama) = tmp;
	}
	return (0);
}

void	*yama(int flag, void *ptr, size_t size)
{
	static t_gc_lst *yama;

	if (flag == CREATE)
		ptr = create(&yama, size);
	else if (flag == ADD)
		ptr = add(&yama, ptr);
	else if (flag == REMOVE)
	{
		if (remove_gc_node(&yama, ptr) == -1)
			printf("NO ALLOCATION FREED, YAMA IS EMPTY !\n");
		ptr = NULL;
	}
	else if (flag == CLEAN_ALL)
	{
		if (clean_all(&yama) == -1)
			printf("NO ALLOCATION FREED, YAMA IS EMPTY !\n");
		ptr = NULL;
	}
	else
		return (printf("THIS YAMA'S FLAG DOESN'T EXIST !\n"), NULL);
	return (ptr);
}


//remplacer printf par ft_printf ou puterror lorsque yama aura ete teste