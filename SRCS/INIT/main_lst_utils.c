/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_lst_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: annabrag <annabrag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 15:58:33 by annabrag          #+#    #+#             */
/*   Updated: 2024/09/02 19:22:15 by annabrag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_main_lst	*main_new_node(char *content)
{
	t_main_lst	*new_node;
	
	new_node = malloc(sizeof(t_main_lst));
	if (new_node == NULL)
		return (NULL);
	new_node->content = ft_strdup(content);
	new_node->next = NULL;
	return (new_node);
}

t_main_lst	*main_last_node(t_main_lst *main)
{
	if (main == NULL)
		return (NULL);
	while (main->next != NULL)
		main = main->next;
	return (main);
}

void	main_add_back(t_main_lst **main, t_main_lst *new_node)
{
	t_main_lst	*tmp;

	if ((*main) == NULL)
		*main = new_node;
	else
	{
		tmp = main_last_node(*main);
		tmp->next = new_node;
	}
}

size_t	get_main_lst_size(t_main_lst **main)
{
	size_t	size;
	t_main_lst *node;

	size = 0;
	node = *main;
	while (node != NULL)
	{
		size++;
		node = node->next;
	}
	return (size);
}
