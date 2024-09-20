/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_main_lst.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: annabrag <annabrag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 16:02:17 by annabrag          #+#    #+#             */
/*   Updated: 2024/09/20 17:43:54 by annabrag         ###   ########.fr       */
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
			(err_msg("malloc", ERR_MALLOC, 0), clean_exit_shell(FAILURE));
		free(head->content);
		head->content = trimmed_token;
		head = head->next;
	}
	return (SUCCESS);
}

int	create_main_lst(t_data *d, char *input)
{
	t_main_lst	*new_node;
	char		**segments;
	int			i;

	lstclear_main(&d->main);
	segments = split_user_input(input);
	if (segments == NULL)
		return (FAILURE);
	(void)yama(ADD, segments, 0);
	i = 0;
	while (segments[i] != NULL)
	{
		new_node = main_lst_new_node(segments[i]);
		if (new_node == NULL)
			(err_msg("malloc", ERR_MALLOC, 0), clean_exit_shell(FAILURE));
		(void)yama(ADD, new_node, 0);
		main_lst_add_back(&d->main, new_node);
		i++;
		d->e_info.cmd_count = i;
		d->e_info.pipe_count = d->e_info.cmd_count - 1;
	}
	free_tab(segments);
	__del_unwanted_whitespaces(d->main);
	return (SUCCESS);
}
