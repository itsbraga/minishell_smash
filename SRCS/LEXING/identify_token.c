/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   identify_token.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: art3mis <art3mis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 23:23:05 by art3mis           #+#    #+#             */
/*   Updated: 2024/09/24 21:49:53 by art3mis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_token_type	__classify(char *token, char *prev)
{
	if (prev != NULL)
	{
		if (ft_strcmp(prev, "<") == 0)
			return (INFILE);
		else if (ft_strcmp(prev, "<<") == 0)
			return (LIMITER);
		else if (ft_strcmp(prev, ">") == 0 || ft_strcmp(prev, ">>") == 0)
			return (OUTFILE);
	}
	if (ft_strcmp(token, "<") == 0)
		return (REDIR_IN);
	else if (ft_strcmp(token, "<<") == 0)
		return (HERE_DOC);
	else if (ft_strcmp(token, ">") == 0)
		return (REDIR_OUT_TRUNC);
	else if (ft_strcmp(token, ">>") == 0)
		return (REDIR_OUT_APPEND);
	else if (prev == NULL || ft_strcmp(prev, "|") == 0)
		return (COMMAND);
	return (WORD);
}

void	lst_tokenization(t_token_dblst *t)
{
	t_token_dblst	*head;
	t_exec_lst		exec;

	ft_bzero(&exec, sizeof(exec));
	head = t;
	while (head != NULL)
	{
		if (head->prev != NULL)
		{
			head->type = __classify(head->content, head->prev->content);
			if (head->prev->type == COMMAND)
				head->type = ARGUMENT;
		}
		else
			head->type = __classify(head->content, NULL);
		if (head->type == HERE_DOC)
			exec.heredoc_nb++;
		printf(CYAN "token_type:\t %d\n" R, head->type);
		head = head->next;
	}
	printf("heredoc count: %d\n", exec.heredoc_nb);
}
