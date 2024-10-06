/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmateo <pmateo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 23:23:05 by art3mis           #+#    #+#             */
/*   Updated: 2024/10/06 21:51:11 by pmateo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_token_type	__classify(char *token, char *prev)
{
	if (prev != NULL)
	{
		if (ft_strcmp(prev, "<<") == 0)
			return (LIMITER);
		else if (ft_strcmp(prev, "<") == 0)
			return (INFILE);
		else if (ft_strcmp(prev, ">") == 0 || ft_strcmp(prev, ">>") == 0)
			return (OUTFILE);
	}
	if (ft_strcmp(token, "<<") == 0)
		return (HERE_DOC);
	else if (ft_strcmp(token, "<") == 0)
		return (REDIR_IN);
	else if (ft_strcmp(token, ">") == 0)
		return (REDIR_OUT_TRUNC);
	else if (ft_strcmp(token, ">>") == 0)
		return (REDIR_OUT_APPEND);
	return (WORD);
}

static void	__find_command(t_token_dblst *t)
{
	t_token_dblst	*current;

	current = t;
	while (current != NULL)
	{
		if (current->type == WORD)
		{
			current->type = COMMAND;
			break ;
		}
		else
			current = current->next;
	}
}

void	lst_tokenization(t_token_dblst *t)
{
	t_token_dblst	*current;

	current = t;
	while (current != NULL)
	{
		if (current->prev != NULL)
			current->type = __classify(current->content, current->prev->content);
		else
			current->type = __classify(current->content, NULL);
		current = current->next;
	}
	__find_command(t);
}
