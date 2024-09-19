/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   identify_token.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: annabrag <annabrag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 23:23:05 by art3mis           #+#    #+#             */
/*   Updated: 2024/09/19 19:38:25 by annabrag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// 
// Ne gere pas le cas ou le prev de la COMMAND est un INFILE: erreur
//
static t_token_type	__classify(char *token, char *prev)
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
	else if (prev == NULL || ft_strcmp(prev, "|") == 0)
		return (COMMAND);
	return (ARGUMENT);
}

// pour char **limiter verif avec heredoc_nb
void	lst_tokenization(t_token_dblst *t, t_exec_lst *exec)
{
	t_token_dblst	*head;

	head = t;
	while (head != NULL)
	{
		if (head->prev != NULL)
		{
			head->type = __classify(head->content, head->prev->content);
			if (head->type == HERE_DOC)
			{
				exec->heredoc_nb++;
				printf("heredoc count: %d\n", exec->heredoc_nb);
			}
			printf("type:\t %d\n", head->type);
		}
		else
		{
			head->type = __classify(head->content, NULL);
			printf("type:\t %d\n", head->type);
		}
		head = head->next;
	}
}
