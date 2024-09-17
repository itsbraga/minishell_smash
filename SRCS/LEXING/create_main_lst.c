/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_main_lst.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: art3mis <art3mis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 16:02:17 by annabrag          #+#    #+#             */
/*   Updated: 2024/09/17 17:23:48 by art3mis          ###   ########.fr       */
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
	char		**segments;
	size_t      i;

	lstclear_main(&g->main);
	segments = split_user_input(input);
	if (segments == NULL)
		return (FAILURE);
	(void)yama(ADD, segments, 0);
	i = 0;
	while (segments[i] != NULL)
	{
		new_node = main_lst_new_node(segments[i]);
		if (new_node == NULL)
			return (free_tab(segments), err_msg("malloc", ERR_MALLOC, 0), 1);
		(void)yama(ADD, new_node, 0);
		main_lst_add_back(&g->main, new_node);
		i++;
		g->info.cmd_count = i;
		g->info.pipe_count = g->info.cmd_count - 1;
	}
	free_tab(segments);
	__del_unwanted_whitespaces(g->main);
	return (SUCCESS);
}
