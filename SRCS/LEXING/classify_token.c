/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   classify_token.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: art3mis <art3mis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 23:23:05 by art3mis           #+#    #+#             */
/*   Updated: 2024/09/10 17:33:10 by art3mis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	__heredoc_case(t_classifier *c)
{
	t_token	*limiter_node;

	if (ft_strcmp(c->elems[c->i], "<<") == 0)
	{
		c->token->type = HEREDOC;
		if (c->elems[c->i + 1] != NULL)
		{
			limiter_node = token_lst_new_node(c->elems[c->i + 1]);
			if (limiter_node == NULL)
				return (err_msg("malloc", ERR_MALLOC, 0), false);
			limiter_node->type = LIMITER;
			token_lst_add_back(&c->token_lst, limiter_node);
			c->i++; // evite de retraiter le token suivant
		}
		return (true);
	}
	return (false);
}

static bool	__append_case(t_classifier *c)
{
	t_token	*outfile_node;
	
	if (ft_strcmp(c->elems[c->i], ">>") == 0)
	{
		c->token->type = APPEND;
		if (c->elems[c->i + 1] != NULL)
		{
			outfile_node = token_lst_new_node(c->elems[c->i + 1]);
			if (outfile_node == NULL)
				return (err_msg("malloc", ERR_MALLOC, 0), false);
			outfile_node->type = OUTFILE;
			token_lst_add_back(&c->token_lst, outfile_node);
			c->i++; // evite de retraiter le token suivant
		}
		return (true);
	}
	return (false);
}

// pas encore gere le cas des PIPE / INFILE / OUTFILE / COMMAND / ARGUMENT
//
// ni quotes
int classify_token(t_classifier *c)
{
	if (__heredoc_case(c) == true)
		return (SUCCESS);
	if (__append_case(c) == true)
		return (SUCCESS);
	// if (ft_strcmp(c->elems[c->i], "|") == 0)
	// 	c->token->type = SEPARATOR;
	if (ft_strcmp(c->elems[c->i], "<") == 0)
		c->token->type = REDIR_IN;
	else if (ft_strcmp(c->elems[c->i], ">") == 0)
		c->token->type = REDIR_OUT;
	return (SUCCESS);
}
