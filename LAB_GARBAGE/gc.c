/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: annabrag <annabrag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 15:33:03 by pmateo            #+#    #+#             */
/*   Updated: 2024/09/19 18:52:43 by annabrag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "gc.h"

static void	*__create(t_gc_lst **yama, size_t size, bool is_tab)
{
	void		*ptr;
	t_gc_lst	*node;

	ptr = malloc(size);
	if (ptr == NULL)
		return (printf("ALLOCATION FAILED !\n"), NULL);
	node = new_gc_node(ptr, is_tab);
	if (node == NULL)
		return (printf("NODE CREATION FAILED !\n"), NULL);
	add_gc_node(yama, node);
	return (ptr);
}

static void	*__add(t_gc_lst **yama, void *ptr, bool is_tab)
{
	t_gc_lst *node;

	node = new_gc_node(ptr, is_tab);
	if (node == NULL)
		return (printf("NODE CREATION FAILED !\n"), NULL);
	add_gc_node(yama, node);
	return (ptr);
}

static void	__free_tab(char **tab)
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

static int	__clean_all(t_gc_lst **yama)
{
	t_gc_lst *tmp;

	if (yama == NULL || *yama == NULL)
		return (-1);
	while ((*yama) != NULL)
	{
		tmp = (*yama)->next;
		(*yama)->next = NULL;
		if ((*yama)->is_tab == true)
			__free_tab((char **)(*yama)->ptr);
		else
		{
			free((*yama)->ptr);
			(*yama)->ptr = NULL;
			free((*yama));
		}
		(*yama) = tmp;
	}
	return (0);
}

void	*yama(int flag, void *ptr, size_t size)
{
	static t_gc_lst *yama;

	if (flag == CREATE)
		ptr = __create(&yama, size, false);
	else if (flag == CREATE_TAB)
		ptr = __create(&yama, size, true);
	else if (flag == ADD)
		ptr = __add(&yama, ptr, false);
	else if (flag == ADD_TAB)
		ptr = __add(&yama, ptr, true);
	else if (flag == REMOVE)
	{
		if (remove_gc_node(&yama, ptr) == -1)
			printf("NO ALLOCATION FREED, YAMA IS EMPTY !\n");
		ptr = NULL;
	}
	else if (flag == CLEAN_ALL)
	{
		if (__clean_all(&yama) == -1)
			printf("NO ALLOCATION FREED, YAMA IS EMPTY !\n");
		ptr = NULL;
	}
	else
		return (printf("THIS YAMA'S FLAG DOESN'T EXIST !\n"), NULL);
	return (ptr);
}


//remplacer printf par ft_printf ou puterror lorsque yama aura ete teste