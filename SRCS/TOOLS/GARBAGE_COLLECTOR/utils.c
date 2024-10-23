/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: annabrag <annabrag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 15:54:10 by pmateo            #+#    #+#             */
/*   Updated: 2024/10/23 19:07:10 by annabrag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tools.h"

void	*search_ptr(t_gc_lst **yama, void *ptr)
{
	t_gc_lst	*curr;

	curr = *yama;
	while (curr != NULL)
	{
		if (curr->ptr == ptr)
			return (curr->ptr);
		curr = curr->next;
	}
	return (NULL);
}

int	handle_remove(t_gc_lst **yama, void *ptr)
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
