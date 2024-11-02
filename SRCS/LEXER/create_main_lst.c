/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_main_lst.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: art3mis <art3mis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 16:02:17 by annabrag          #+#    #+#             */
/*   Updated: 2024/11/02 00:59:37 by art3mis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser_lexer.h"

static void	__init_exec_info(t_data *d)
{
	d->info = yama(CREATE, NULL, sizeof(t_exec_info));
	secure_malloc(d->info, true);
	ft_bzero(d->info, sizeof(t_exec_info));
	d->info->fd[0] = -1;
	d->info->fd[1] = -1;
}

static char	**__get_all_segments(char *input)
{
	t_parser	p;
	size_t		input_len;

	if (input == NULL || input[0] == '\0')
		return (NULL);
	ft_bzero(&p, sizeof(t_parser));
	p.input = input;
	input_len = ft_strlen(p.input);
	p.segment = yama(CREATE_TAB, NULL, (sizeof(char *) * (input_len + 1)));
	secure_malloc(p.segment, true);
	while (p.input[p.i] != '\0')
	{
		if (parse_input(&p) == BAD_USAGE)
			return (NULL);
	}
	p.segment[p.seg_count] = NULL;
	return (p.segment);
}

int	create_main_lst(t_data *d, char *input)
{
	t_main_lst	*new_node;
	char		**segments;
	int			i;

	if (unclosed_quotes(input) == true)
		return (err_msg(NULL, YELLOW "warning: unclosed quotes" R, 0), FAILURE);
	__init_exec_info(d);
	segments = __get_all_segments(input);
	if (segments == NULL)
		return (FAILURE);
	i = 0;
	while (segments[i] != NULL)
	{
		new_node = main_lst_new_node(segments[i]);
		if (new_node == NULL)
			return ((void)yama(REMOVE, segments, 0), FAILURE);
		main_lst_add_back(&(d->main), new_node);
		i++;
		d->info->cmd_count = i;
		d->info->pipe_count = d->info->cmd_count - 1;
	}
	(void)yama(REMOVE, segments, 0);
	del_unwanted_whitespaces(d->main);
	return (SUCCESS);
}
