/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: annabrag <annabrag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 19:35:48 by art3mis           #+#    #+#             */
/*   Updated: 2024/11/02 21:21:58 by annabrag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser_lexer.h"

static void	__init_parser(t_parser *p)
{
	p->closed_quotes[0] = true;
	p->closed_quotes[1] = true;
	p->start = p->i;
}

static int	__handle_pipe_error(t_parser *p)
{
	if (p->input[p->i] == '|')
	{
		p->i++;
		if (p->input[p->i] == '|')
			return (err_msg(NULL, "||", 2), BAD_USAGE);
		while (p->input[p->i] != '\0' && ft_isspace(p->input[p->i]) == 1)
			p->i++;
		if (p->input[p->i] == '|' || p->input[p->i] == '\0')
			return (err_msg(NULL, "|", 2), BAD_USAGE);
	}
	return (SUCCESS);
}

static int	__first_check(t_parser *p)
{
	while (ft_isspace(p->input[p->i]) == 1)
		p->i++;
	if (p->input[p->i] == '\0')
		return (SUCCESS);
	else if (p->input[p->i] == '|')
	{
		if (__handle_pipe_error(p) == BAD_USAGE)
			return (BAD_USAGE);
	}
	return (SUCCESS);
}

int	parse_input(t_parser *p)
{
	t_redir_parser	rp;

	__init_parser(p);
	if (__first_check(p) == BAD_USAGE || check_redir_order(p, &rp) == BAD_USAGE)
		return (ft_exit_status(BAD_USAGE, ADD));
	p->i = p->start;
	while (p->input[p->i] != '\0')
	{
		get_closed_quotes(p->input[p->i], p->closed_quotes);
		if (p->input[p->i] == '|' && p->closed_quotes[0] == true
			&& p->closed_quotes[1] == true)
			break ;
		p->i++;
	}
	p->tmp = ft_strldup(p->input + p->start, (p->i - p->start));
	secure_malloc(p->tmp, false);
	(void)yama(ADD, p->tmp, 0);
	p->segment[p->seg_count] = p->tmp;
	p->seg_count++;
	if (p->closed_quotes[0] == true && p->closed_quotes[1] == true)
	{
		if (__handle_pipe_error(p) == BAD_USAGE)
			return (ft_exit_status(BAD_USAGE, ADD));
	}
	return (SUCCESS);
}
