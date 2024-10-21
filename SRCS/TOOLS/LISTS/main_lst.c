/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_lst.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: art3mis <art3mis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 15:58:33 by annabrag          #+#    #+#             */
/*   Updated: 2024/10/21 00:13:53 by art3mis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_main_lst	*main_lst_new_node(char *content)
{
	t_main_lst	*new_node;

	new_node = yama(CREATE, NULL, sizeof(t_main_lst));
	secure_malloc(new_node, true);
	new_node->content = ft_strdup(content);
	if (new_node->content == NULL)
	secure_malloc(new_node->content, true);
	(void)yama(ADD, new_node->content, 0);
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
	t_main_lst	*current;

	size = 0;
	current = *main;
	while (current != NULL)
	{
		size++;
		current = current->next;
	}
	return (size);
}

void	del_unwanted_whitespaces(t_main_lst *main)
{
	t_main_lst	*current;
	char		*trimmed_token;

	current = main;
	while (current != NULL)
	{
		trimmed_token = ft_strtrim(current->content, " ");
		secure_malloc(trimmed_token, true);
		(void)yama(ADD, trimmed_token, 0);
		(void)yama(REMOVE, current->content, 0);
		current->content = trimmed_token;
		(void)yama(ADD, current->content, 0);
		current = current->next;
	}
}
