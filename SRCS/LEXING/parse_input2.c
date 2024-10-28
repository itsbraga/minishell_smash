/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: annabrag <annabrag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 18:36:43 by art3mis           #+#    #+#             */
/*   Updated: 2024/10/28 16:48:54 by annabrag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing_lexing.h"

static int	__specific_cases(t_parser *p)
{
	if (p->input[p->i] == '>' || p->input[p->i] == '<')
	{
		p->next_redir = p->input[p->i];
		p->next_count = 0;
		while (p->input[p->i + p->next_count] == p->next_redir)
			p->next_count++;
		if (p->next_count >= 3 && p->next_redir == '<')
			return (err_msg(NULL, "<<<", 2), BAD_USAGE);
		else if (p->next_count == 2 && p->next_redir == '<')
			return (err_msg(NULL, "<<", 2), BAD_USAGE);
		else if (p->next_count >= 2 && p->next_redir == '>')
			return (err_msg(NULL, ">>", 2), BAD_USAGE);
		if (p->input[p->i + p->next_count] == '\0')
		{
			if (p->next_redir == '>')
				return (err_msg(NULL, ">", 2), BAD_USAGE);
			return (err_msg(NULL, "<", 2), BAD_USAGE);
		}
	}
	return (SUCCESS);
}

static int	__different_cases(t_parser *p)
{
	char	curr_char;
	size_t	start_i;
	
	start_i = p->i;
	curr_char = p->input[p->i];
	p->rcount = 0;
	while (p->input[p->i] == curr_char)
	{
		p->rcount++;
		p->i++;
	}
	if (p->rcount > 2)
	{
		p->i = start_i;
		if (curr_char == '>')
			return (err_msg(NULL, ">>", 2), BAD_USAGE);
	}
	while (ft_isspace(p->input[p->i]) == 1)
		p->i++;
	if (p->input[p->i] == '\0')
		return (err_msg(NULL, "newline", 2), BAD_USAGE);
	if (__specific_cases(p) == BAD_USAGE)
		return (BAD_USAGE);
	return (SUCCESS);
}

static int	__pipe_surrounded_by_redirs(t_parser *p)
{
	if (p->input[p->i] == '|')
	{
		if (p->i > 0 && (p->input[p->i - 1] == '>' || p->input[p->i - 1] == '<')
			&& (p->input[p->i + 1] == '>' || p->input[p->i + 1] == '<'))
		{
			p->i = p->orig_i;
			return (err_msg(NULL, "|", 2), BAD_USAGE);
		}
	}
	return (SUCCESS);
}

int	check_order(t_parser *p)
{
	p->orig_i = p->i;
	while (p->input[p->i] != '\0')
	{
		if (p->input[p->i] == '>' || p->input[p->i] == '<')
		{
			if (__different_cases(p) == BAD_USAGE)
			{
				p->i = p->orig_i;
				return (BAD_USAGE);
			}
			continue ;
		}
		if (__pipe_surrounded_by_redirs(p) == BAD_USAGE)
		{
			p->i = p->orig_i;
			return (BAD_USAGE);
		}
		p->i++;
	}
	p->i = p->orig_i;
	return (SUCCESS);
}
