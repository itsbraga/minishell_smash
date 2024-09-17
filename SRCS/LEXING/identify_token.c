/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   identify_token.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: art3mis <art3mis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 23:23:05 by art3mis           #+#    #+#             */
/*   Updated: 2024/09/17 18:53:24 by art3mis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token_type	classify_token(char *token, char *prev)
{
	if (ft_strcmp(token, "<") == 0)
		return (REDIR_IN);
	else if (ft_strcmp(token, "<<") == 0)
		return (HERE_DOC);
	else if (ft_strcmp(token, ">") == 0)
		return (TRUNC);
	else if (ft_strcmp(token, ">>") == 0)
		return (APPEND);
	else if (prev != NULL)
	{
		if (ft_strcmp(prev, "<") == 0)
			return (INFILE);
		else if (ft_strcmp(prev, "<<") == 0)
			return (LIMITER);
		else if (ft_strcmp(prev, ">") == 0 || ft_strcmp(prev, ">>") == 0)
			return (OUTFILE);
	}
	else if (ft_strchr(token, '"') != NULL || ft_strchr(token, '\'') != NULL)
		return (IN_QUOTE);
	else if (prev == NULL || ft_strcmp(prev, "|") == 0)
		return (COMMAND);
	return (ARGUMENT);
}

void	lst_tokenization(t_token_dblst *t)
{
	t_token_dblst	*head;

	head = t;
	while (head != NULL)
	{
		if (head->prev != NULL)
		{
			head->type = classify_token(head->content, head->prev->content);
			printf("type:\t %d\n", head->type);
		}
		else
		{
			head->type = classify_token(head->content, NULL);
			printf("type:\t %d\n", head->type);
		}
		head = head->next;
	}
}
