/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: annabrag <annabrag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 18:36:43 by art3mis           #+#    #+#             */
/*   Updated: 2024/10/23 23:47:51 by annabrag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing_lexing.h"

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

int	check_order(t_parser *p);
