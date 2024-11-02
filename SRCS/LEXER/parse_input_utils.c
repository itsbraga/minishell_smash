/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: annabrag <annabrag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 18:36:43 by art3mis           #+#    #+#             */
/*   Updated: 2024/11/02 21:22:10 by annabrag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser_lexer.h"

static int	__handle_redir_error(t_parser *p, t_redir_parser *rp)
{
	rp->curr_char = p->input[p->i];
	while (p->input[p->i] == rp->curr_char)
	{
		rp->rcount++;
		p->i++;
	}
	while (ft_isspace(p->input[p->i]) == 1)
		p->i++;
	if ((rp->curr_char == '>' && p->input[p->i] == '<')
		|| (rp->curr_char == '<' && p->input[p->i] == '>'))
		return (handle_bidirections(rp));
	if (rp->rcount >= 0 && (p->input[p->i] == '>' || p->input[p->i] == '<'))
		return (handle_spaced_sequence(rp, p));
	if (p->input[p->i] == '|')
		return (handle_redir_near_pipe(rp));
	if (p->input[p->i] == '\0')
		return (err_msg(NULL, "newline", 2), BAD_USAGE);
	return (SUCCESS);
}

int	check_redir_order(t_parser *p, t_redir_parser *rp)
{
	ft_bzero(rp, sizeof(t_redir_parser));
	while (p->input[p->i] != '\0')
	{
		if (p->input[p->i] == '>' || p->input[p->i] == '<')
		{
			if (__handle_redir_error(p, rp) == BAD_USAGE)
				return (BAD_USAGE);
			continue ;
		}
		p->i++;
	}
	return (SUCCESS);
}
