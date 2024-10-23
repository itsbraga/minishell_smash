/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: annabrag <annabrag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 19:35:48 by art3mis           #+#    #+#             */
/*   Updated: 2024/10/23 19:00:45 by annabrag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing-lexing.h"

static int	__front_check(t_parser *p)
{
	while (ft_isspace(p->input[p->i]) == 1)
		p->i++;
	if (p->input[p->i] == '\0')
		return (SUCCESS);
	if (p->input[p->i] == '|')
	{
		err_msg(NULL, "|", 2);
		return (BAD_USAGE);
	}
	return (SUCCESS);
}

static void	__init_parser(t_parser *p)
{
	p->closed_quotes[0] = true;
	p->closed_quotes[1] = true;
	p->start = p->i;
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
	char	*tmp;

	__init_parser(p);
	if (__front_check(p) == BAD_USAGE)
		return (BAD_USAGE);
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
	tmp = ft_strldup(p->input + p->start, (p->i - p->start));
	(secure_malloc(tmp, false), (void)yama(ADD, tmp, 0));
	p->segment[p->seg_count++] = tmp;
	if (p->closed_quotes[0] == true && p->closed_quotes[1] == true)
	{
		if (__pipe_check_end(p) == BAD_USAGE)
			return (BAD_USAGE);
	}
	return (SUCCESS);
}
