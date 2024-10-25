/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: annabrag <annabrag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 19:35:48 by art3mis           #+#    #+#             */
/*   Updated: 2024/10/25 19:13:49 by annabrag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing_lexing.h"

static void	__init_parser(t_parser *p)
{
	p->closed_quotes[0] = true;
	p->closed_quotes[1] = true;
	p->start = p->i;
}

static int	__first_check(t_parser *p)
{
	while (ft_isspace(p->input[p->i]) == 1)
		p->i++;
	if (p->input[p->i] == '\0')
		return (BAD_USAGE);
	else if (p->input[p->i] == '|')
		return (err_msg(NULL, "|", 2), BAD_USAGE);
	return (SUCCESS);
}

static int	__pipe_check_end(t_parser *p)
{
	if (p->input[p->i] == '|')
	{
		p->i++;
		if (p->input[p->i] == '|')
		{
			err_msg(NULL, "||", 2);
			return (BAD_USAGE);
		}
		while (p->input[p->i] != '\0'
			&& ft_isspace(p->input[p->i]) == 1)
			p->i++;
		if (p->input[p->i] == '|' || p->input[p->i] == '\0')
		{
			err_msg(NULL, "|", 2);
			return (BAD_USAGE);
		}
	}
	return (SUCCESS);
}

int	parse_input(t_parser *p)
{
	__init_parser(p);
	if (__first_check(p) == BAD_USAGE || check_order(p) == BAD_USAGE)
		return (BAD_USAGE);
	p->i = p->start;
	while (p->input[p->i] != '\0')
	{
		if (p->input[p->i] == '\'')
			p->closed_quotes[0] = switch_bool(p->closed_quotes[0]);
		else if (p->input[p->i] == '"')
			p->closed_quotes[1] = switch_bool(p->closed_quotes[1]);
		else if (p->input[p->i] == '|' && p->closed_quotes[0] == true
			&& p->closed_quotes[1] == true)
			break ;
		p->i++;
	}
	p->tmp = ft_strldup(p->input + p->start, (p->i - p->start));
	secure_malloc(p->tmp, false);
	(void)yama(ADD, p->tmp, 0);
	p->segment[p->seg_count++] = p->tmp;
	if (p->closed_quotes[0] == true && p->closed_quotes[1] == true)
	{
		if (__pipe_check_end(p) == BAD_USAGE)
			return (BAD_USAGE);
	}
	return (SUCCESS);
}
