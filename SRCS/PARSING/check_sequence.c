/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_sequence.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: art3mis <art3mis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 18:36:43 by art3mis           #+#    #+#             */
/*   Updated: 2024/10/21 02:29:30 by art3mis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	__different_cases(char *content, t_token_parser *p)
{
	if (p->redir == '>' && p->count > 2)
	{
		err_msg(NULL, ">>", 2);
		return (FAILURE);
	}
	else if (p->redir == '<' && p->count > 2)
	{
		err_msg(NULL, "<<", 2);
		return (FAILURE);
	}
	else if (p->redir == '>' && p->count == 1 && content[p->j] == '>')
	{
		err_msg(NULL, ">", 2);
		return (FAILURE);
	}
	else if (p->redir == '<' && p->count == 1 && content[p->j] == '<')
	{
		err_msg(NULL, "<", 2);
		return (FAILURE);
	}
	else if (content[p->j] == '\0')
	{
		err_msg(NULL, "newline", 2);
		return (FAILURE);
	}
	else if (content[p->j] == '|')
	{
		err_msg(NULL, "|", 2);
		return (FAILURE);
	}
	return (SUCCESS);
}

int	check_redir_sequence(char *content, t_token_parser *p)
{
	while (content[p->j] != '\0')
	{
		if (is_redir(content) == true)
		{
			p->redir = content[p->j];
			p->count = 1;
			p->j++;
			while (content[p->j] == p->redir)
			{
				p->count++;
				p->j++;
			}
			if (__different_cases(content, p) == FAILURE)
				return (FAILURE);
		}
		else
			p->j++;
	}
	return (SUCCESS);
}
