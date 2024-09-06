/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_main_lst.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: art3mis <art3mis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 16:02:17 by annabrag          #+#    #+#             */
/*   Updated: 2024/09/06 02:14:31 by art3mis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	__del_unwanted_char(t_main_lst *main)
{
	t_main_lst  *head;
	char        *trimmed_token;
	size_t		len;

	head = main;
	len = ft_strlen(head->content);
	while (head != NULL)
	{
		if (((head->content[0] == '"') && (head->content[len - 1] == '"'))
			|| ((head->content[1] == '\'') && (head->content[len - 1] == '\'')))
		{
			head = head->next;
			continue ;
		}
		trimmed_token = ft_strtrim(head->content, " ");
		if (trimmed_token == NULL)
			return (err_msg(NULL, "cannot trim token"), FAILURE);
		free(head->content);
		head->content = trimmed_token;
		head = head->next;
	}
	return (SUCCESS);
}

int	create_main_lst(t_global *g, char *input)
{
	t_main_lst	*new_node;
	char		**tokens;
	size_t      i;

	lstclear_main(&g->main);
	tokens = split_user_input(input);
	if (tokens == NULL)
		return (FAILURE);
	i = 0;
	while (tokens[i] != NULL)
	{
		new_node = main_new_node(tokens[i]);
		if (new_node == NULL)
		{
			free_tab(tokens);
			return (err_msg("malloc", ERR_MALLOC), FAILURE);
		}
		main_add_back(&g->main, new_node);
		i++;
	}
	free_tab(tokens);
	__del_unwanted_char(g->main);
	return (SUCCESS);
}
