/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_main_lst.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: art3mis <art3mis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 16:02:17 by annabrag          #+#    #+#             */
/*   Updated: 2024/09/27 00:02:48 by art3mis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**__get_all_segments(char *input)
{
	t_parser	p;
	size_t		input_len;
	
	ft_bzero(&p, sizeof(p));
	p.user_input = input;
	if (p.user_input == NULL || p.user_input[0] == '\0')
		return (NULL);
	input_len = ft_strlen(p.user_input);
	p.segment = yama(CREATE, NULL, (sizeof(char *) * (input_len + 1)));
	if (p.segment == NULL)
		(err_msg("malloc", ERR_MALLOC, 0), clean_exit_shell(FAILURE));
	while (p.user_input[p.i] != '\0')
		parse_input(&p);
	p.segment[p.seg_count] = NULL;
	return (p.segment);
}

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
	segments = __get_all_segments(input);
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
		d->info.cmd_count = i;
		d->info.pipe_count = d->info.cmd_count - 1;
	}
	((void)yama(REMOVE, segments, 0), __del_unwanted_whitespaces(d->main));
	return (SUCCESS);
}
