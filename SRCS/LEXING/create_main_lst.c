/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_main_lst.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: annabrag <annabrag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 16:02:17 by annabrag          #+#    #+#             */
/*   Updated: 2024/10/09 21:30:33 by annabrag         ###   ########.fr       */
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
	secure_malloc(p.segment);
	while (p.user_input[p.i] != '\0')
		parse_input(&p);
	p.segment[p.seg_count] = NULL;
	return (p.segment);
}

static void	__del_unwanted_whitespaces(t_main_lst *main)
{
	t_main_lst	*current;
	char		*trimmed_token;

	current = main;
	while (current != NULL)
	{
		trimmed_token = ft_strtrim(current->content, " ");
		secure_malloc(trimmed_token);
		(void)yama(ADD, trimmed_token, 0);
		free(current->content);
		current->content = trimmed_token;
		current = current->next;
	}
}

int	create_main_lst(t_data *d, char *input)
{
	t_main_lst	*new_node;
	char		**segments;
	int			i;

	if (unclosed_quotes(input) == true)
		return (err_msg(NULL, YELLOW "WARNING: unclosed quotes" R, 0), FAILURE);
	d->info = yama(CREATE, NULL, sizeof(t_exec_info));
	ft_bzero((d->info), sizeof(t_exec_info));
	lstclear_main(&(d->main));
	segments = __get_all_segments(input);
	secure_malloc2(segments, false);
	(void)yama(ADD, segments, 0);
	i = 0;
	while (segments[i] != NULL)
	{
		new_node = main_lst_new_node(segments[i]);
		secure_malloc(new_node);
		(void)yama(ADD, new_node, 0);
		main_lst_add_back(&(d->main), new_node);
		i++;
		d->info->cmd_count = i;
		d->info->pipe_count = d->info->cmd_count - 1;
	}
	((void)yama(REMOVE, segments, 0), __del_unwanted_whitespaces(d->main));
	return (SUCCESS);
}
