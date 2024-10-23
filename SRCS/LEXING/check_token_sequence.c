/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_token_sequence.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: annabrag <annabrag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 18:36:43 by art3mis           #+#    #+#             */
/*   Updated: 2024/10/23 18:41:09 by annabrag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing-lexing.h"

static int	__different_cases(char *content, t_token_parser *p)
{
	if (p->redir == '>' && p->count > 2)
		return (err_msg(NULL, ">>", 2), BAD_USAGE);
	else if (p->redir == '<' && p->count > 2)
		return (err_msg(NULL, "<<", 2), BAD_USAGE);
	else if (p->redir == '>' && p->count == 1 && content[p->j] == '>')
		return (err_msg(NULL, ">", 2), BAD_USAGE);
	else if (p->redir == '<' && p->count == 1 && content[p->j] == '<')
		return (err_msg(NULL, "<", 2), BAD_USAGE);
	else if (content[p->j] == '\0')
		return (err_msg(NULL, "newline", 2), BAD_USAGE);
	return (SUCCESS);
}

int	check_token_sequence(t_data *d, t_token_dblst *t)
{
	t_token_dblst	*curr;

	curr = t;
	while (curr != NULL)
	{
		if (IS_REDIR(curr) == true && curr->next == NULL)
			return (err_msg(NULL, "newline", 2), BAD_USAGE);
		else if ()
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
				return (BAD_USAGE);
		}
		else
			curr = curr->next;
	}
	return (SUCCESS);
}
