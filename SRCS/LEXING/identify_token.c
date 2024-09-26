/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   identify_token.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: art3mis <art3mis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 23:23:05 by art3mis           #+#    #+#             */
/*   Updated: 2024/09/27 01:07:46 by art3mis          ###   ########.fr       */
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
	else if (prev == NULL || ft_strcmp(token, "|") == 0)
		return (COMMAND);
	return (WORD);
}

void	lst_tokenization(t_token_dblst *t)
{
	t_token_dblst	*head;

	head = t;
	while (head != NULL)
	{
		if (head->prev != NULL)
			head->type = __classify(head->content, head->prev->content);
		else
			head->type = __classify(head->content, NULL);
		if (head->type == HERE_DOC)
			head->exec->heredoc_nb++;
		head = head->next;
	}
	printf(ITAL "\nHERE_DOC count: %d\n\n" R, head->exec->heredoc_nb);
}
