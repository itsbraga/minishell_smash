/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input_utils2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: annabrag <annabrag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 02:02:07 by annabrag          #+#    #+#             */
/*   Updated: 2024/11/02 21:19:16 by annabrag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser_lexer.h"

int	handle_bidirections(t_redir_parser *rp)
{
	if (rp->curr_char == '>')
		return (err_msg(NULL, "<", 2), BAD_USAGE);
	else
		return (err_msg(NULL, ">", 2), BAD_USAGE);
}

static int	__db_redir(t_redir_parser *rp)
{
	if (rp->is_db_redir == true)
	{
		if (rp->curr_char == '>')
			return (err_msg(NULL, ">>", 2), BAD_USAGE);
		else
			return (err_msg(NULL, "<<", 2), BAD_USAGE);
	}
	else
	{
		if (rp->curr_char == '>')
			return (err_msg(NULL, ">", 2), BAD_USAGE);
		else
			return (err_msg(NULL, "<", 2), BAD_USAGE);
	}
	return (SUCCESS);
}

int	handle_spaced_sequence(t_redir_parser *rp, t_parser *p)
{
	if (rp->rcount >= 2)
		rp->is_db_redir = true;
	else
		rp->is_db_redir = false;
	rp->next_char = p->input[p->i];
	while (rp->next_char == rp->curr_char || ft_isspace(rp->next_char) == 1)
	{
		if (rp->next_char == rp->curr_char)
			rp->count_next++;
		else
			rp->space++;
		p->i++;
		rp->next_char = p->input[p->i];
	}
	if (rp->count_next > 0)
		return (__db_redir(rp));
	return (SUCCESS);
}

int	handle_redir_near_pipe(t_redir_parser *rp)
{
	if (rp->rcount <= 3)
		return (err_msg(NULL, "|", 2), BAD_USAGE);
	else
	{
		rp->rcount2 = rp->rcount - 3;
		if (rp->curr_char == '<')
		{
			if (rp->rcount2 == 1)
				return (err_msg(NULL, "<", 2), BAD_USAGE);
			else if (rp->rcount2 == 2)
				return (err_msg(NULL, "<<", 2), BAD_USAGE);
			else
				return (err_msg(NULL, "<<<", 2), BAD_USAGE);
		}
		else if (rp->curr_char == '>')
			return (err_msg(NULL, ">>", 2), BAD_USAGE);
	}
	return (SUCCESS);
}
