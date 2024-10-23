/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: annabrag <annabrag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 23:23:05 by art3mis           #+#    #+#             */
/*   Updated: 2024/10/23 18:40:29 by annabrag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing-lexing.h"

static t_token_type	__classify(char *token, char *prev)
{
	if (ft_strncmp(token, "<<", 2) == 0)
		return (HERE_DOC);
	else if (ft_strncmp(token, "<", 1) == 0)
		return (REDIR_IN);
	else if (ft_strncmp(token, ">", 1) == 0)
		return (REDIR_OUT_TRUNC);
	else if (ft_strncmp(token, ">>", 2) == 0)
		return (REDIR_OUT_APPEND);
	if (prev != NULL)
	{
		if (ft_strncmp(prev, "<<", 2) == 0)
			return (LIMITER);
		else if (ft_strncmp(prev, "<", 1) == 0)
			return (INFILE);
		else if (ft_strncmp(prev, ">", 1) == 0
			|| ft_strncmp(prev, ">>", 2) == 0)
			return (OUTFILE);
	}
	return (WORD);
}

static void	__find_command(t_token_dblst *t)
{
	t_token_dblst	*curr;

	curr = t;
	while (curr != NULL)
	{
		if (curr->type == WORD)
		{
			curr->type = COMMAND;
			break ;
		}
		else
			curr = curr->next;
	}
}

void	lst_tokenization(t_token_dblst *t)
{
	t_token_dblst	*curr;

	if (t == NULL || t->content == NULL)
		return ;
	curr = t;
	while (curr != NULL)
	{
		if (curr->prev != NULL)
			curr->type = __classify(curr->content, curr->prev->content);
		else
			curr->type = __classify(curr->content, NULL);
		curr = curr->next;
	}
	__find_command(t);
}
