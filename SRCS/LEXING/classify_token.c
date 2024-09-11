/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   classify_token.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: annabrag <annabrag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 23:23:05 by art3mis           #+#    #+#             */
/*   Updated: 2024/09/11 20:43:13 by annabrag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// pas encore gere le cas des PIPE / INFILE / OUTFILE / COMMAND / ARGUMENT
t_token_type	classify_token(t_classifier *c)
{
	if (ft_strcmp(c->seg_elems[c->i], "<") == 0)
		return (REDIR_IN);
	else if (ft_strcmp(c->seg_elems[c->i], "<<") == 0)
		return (HERE_DOC);
	else if (ft_strcmp(c->seg_elems[c->i], ">") == 0)
		return (TRUNC);
	else if (ft_strcmp(c->seg_elems[c->i], ">>") == 0)
		return (APPEND);
	return (-1);
}
	// INFILE CASE
	// OUTFILE CASE
	// else if (is_command == true)
	// 	return (COMMAND);
	// else
	// 	return (ARGUMENT);