/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_sequence.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: annabrag <annabrag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 18:36:43 by art3mis           #+#    #+#             */
/*   Updated: 2024/10/23 16:22:17 by annabrag         ###   ########.fr       */
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

int	check_redir_sequence(char *content, t_token_parser *p)
{
	t_data	*d;

	d = data_struct();
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
				return (d->last_exit_status = BAD_USAGE);
		}
		else
			p->j++;
	}
	return (d->last_exit_status = SUCCESS);
}
