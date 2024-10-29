/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: annabrag <annabrag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 18:36:43 by art3mis           #+#    #+#             */
/*   Updated: 2024/10/29 19:55:25 by annabrag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing_lexing.h"

static int	__handle_redir_near_pipe(t_parser *p)
{
	if (p->rcount <= 3)
		return (err_msg(NULL, "|", 2), BAD_USAGE);
	else
	{
		p->rcount2 = p->rcount - 3;
		if (p->curr_char == '<')
		{
			if (p->rcount2 == 1)
				return (err_msg(NULL, "<", 2), BAD_USAGE);
			else if (p->rcount2 == 2)
				return (err_msg(NULL, "<<", 2), BAD_USAGE);
			else
				return (err_msg(NULL, "<<<", 2), BAD_USAGE);	
		}
		else if (p->curr_char == '>')
			return (err_msg(NULL, ">>", 2), BAD_USAGE);
	}
	return (SUCCESS);
}

static int	__handle_redir_error(t_parser *p)
{
	p->curr_char = p->input[p->i];
	p->rcount = 0;
	while (p->input[p->i] == p->curr_char)
	{
		p->rcount++;
		p->i++;
	}
	while (ft_isspace(p->input[p->i]) == 1)
		p->i++;
	if (p->input[p->i] == '|')
	{
		if (__handle_redir_near_pipe(p) == BAD_USAGE)
			return (BAD_USAGE);
	}
	if (p->input[p->i] == '\0')
		return (err_msg(NULL, "newline", 2), BAD_USAGE);
	return (SUCCESS);
}

int	check_redir_order(t_parser *p)
{
	while (p->input[p->i] != '\0')
	{
		if (p->input[p->i] == '>' || p->input[p->i] == '<')
		{
			if (__handle_redir_error(p) == BAD_USAGE)
				return (BAD_USAGE);
			continue ;
		}
		p->i++;
	}
	return (SUCCESS);
}
