/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_main_lst.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: art3mis <art3mis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 16:02:17 by annabrag          #+#    #+#             */
/*   Updated: 2024/09/24 15:24:47 by art3mis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	__del_unwanted_whitespaces(t_main_lst *main)
{
	t_main_lst  *head;
	char        *trimmed_token;

	head = main;
	while (head != NULL)
	{
		trimmed_token = ft_strtrim(head->content, " ");
		if (trimmed_token == NULL)
			(err_msg("malloc", ERR_MALLOC, 0), clean_exit_shell(FAILURE));
		(void)yama(ADD, trimmed_token, 0);
		free(head->content);
		head->content = trimmed_token;
		head = head->next;
	}
}

int	create_main_lst(t_data *d, char *input)
{
	t_main_lst	*new_node;
	char		**segments;
	int			i;

	if (unclosed_quotes(input) == true)
		return (err_msg(NULL, YELLOW "WARNING: unclosed quotes" R, 0), FAILURE);
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
	((void)yama(REMOVE, segments, 0), __del_unwanted_whitespaces(d->main));
	return (SUCCESS);
}
