/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_lst.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: art3mis <art3mis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 15:58:33 by annabrag          #+#    #+#             */
/*   Updated: 2024/11/02 01:09:32 by art3mis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tools.h"

t_main_lst	*main_lst_new_node(char *content)
{
	t_main_lst	*new_node;

	new_node = malloc(sizeof(t_main_lst));
	secure_malloc(new_node, true);
	new_node->content = ft_strdup(content);
	secure_malloc(new_node->content, true);
	new_node->next = NULL;
	return (new_node);
}

static t_main_lst	*__main_lst_last_node(t_main_lst *main)
{
	if (main == NULL)
		return (NULL);
	while (main->next != NULL)
		main = main->next;
	return (main);
}

void	main_lst_add_back(t_main_lst **main, t_main_lst *new_node)
{
	t_main_lst	*tmp;

	if ((*main) == NULL)
		*main = new_node;
	else
	{
		tmp = __main_lst_last_node(*main);
		tmp->next = new_node;
	}
}

size_t	get_main_lst_size(t_main_lst **main)
{
	size_t		size;
	t_main_lst	*curr;

	size = 0;
	curr = *main;
	while (curr != NULL)
	{
		size++;
		curr = curr->next;
	}
	return (size);
}

void	del_unwanted_whitespaces(t_main_lst *main)
{
	t_main_lst	*curr;
	char		*trimmed_token;

	curr = main;
	while (curr != NULL)
	{
		trimmed_token = ft_strtrim(curr->content, " ");
		secure_malloc(trimmed_token, true);
		free(curr->content);
		curr->content = trimmed_token;
		curr = curr->next;
	}
}
