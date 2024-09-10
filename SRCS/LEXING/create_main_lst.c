/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_main_lst.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: art3mis <art3mis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 16:02:17 by annabrag          #+#    #+#             */
/*   Updated: 2024/09/10 16:47:00 by art3mis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	__del_unwanted_whitespaces(t_main_lst *main)
{
	t_main_lst  *head;
	char        *trimmed_token;
	size_t		len;

	head = main;
	len = ft_strlen(head->content) - 1;
	while (head != NULL)
	{
		if (((head->content[0] == '"') && (head->content[len] == '"'))
			|| ((head->content[1] == '\'') && (head->content[len] == '\'')))
		{
			head = head->next;
			continue ;
		}
		trimmed_token = ft_strtrim(head->content, " ");
		if (trimmed_token == NULL)
			return (err_msg(NULL, "cannot trim token", 0), FAILURE);
		free(head->content);
		head->content = trimmed_token;
		head = head->next;
	}
	return (SUCCESS);
}

int	create_main_lst(t_global *g, char *input)
{
	t_main_lst	*new_node;
	char		**elems;
	size_t      i;

	lstclear_main(&g->main);
	elems = split_user_input(input);
	if (elems == NULL)
		return (FAILURE);
	i = 0;
	while (elems[i] != NULL)
	{
		new_node = main_lst_new_node(elems[i]);
		if (new_node == NULL)
		{
			free_tab(elems);
			return (err_msg("malloc", ERR_MALLOC, 0), FAILURE);
		}
		main_lst_add_back(&g->main, new_node);
		i++;
	}
	free_tab(elems);
	__del_unwanted_whitespaces(g->main);
	return (SUCCESS);
}
