/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmateo <pmateo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 15:33:03 by pmateo            #+#    #+#             */
/*   Updated: 2024/09/14 17:45:09 by pmateo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "gc.h"

void	*create(t_gc_lst **yama, size_t	size)
{
	void	*ptr;
	t_gc_lst *node;

	ptr = malloc(size);
	if (ptr == NULL)
		return (NULL, printf("ALLOCATION FAILED !\n"));
	node = new_gc_node(ptr);
	if (node == NULL)
		return (NULL, printf("NODE CREATION FAILED !\n"));
	add_gc_node(yama, node);
	return (ptr);
}

void	*add(t_gc_lst **yama, void *ptr)
{
	t_gc_lst *node;

	node = new_gc_node(ptr);
	if (node == NULL)
		return (NULL, printf("NODE CREATION FAILED !\n"));
	add_gc_node(yama, node);
	return (ptr);
}

int	clean_all(t_gc_lst **yama)
{
	t_gc_lst *node;
	t_gc_lst *tmp;

	if (yama == NULL || *yama == NULL)
		return (-1);
	node = *yama;
	while (node != NULL)
	{
		tmp = node->next;
		node->next = NULL;
		free(node->ptr);
		free(node);
		node = tmp;
	}
	return (0);
}

void	*yama(int flag, void *ptr, size_t size)
{
	t_gc_lst *yama;

	yama = NULL;
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
	else if (flag == clean_all)
	{
		if (clean_all(&yama) == -1)
			printf("NO ALLOCATION FREED, YAMA IS EMPTY !\n");
		ptr = NULL;
	}
	else
		return (NULL, printf("THIS YAMA'S FLAG DOESN'T EXIST !\n"));
	return (ptr);
}


//remplacer printf par ft_printf ou puterror lorsque yama aura ete teste