/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   identify_token.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: annabrag <annabrag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 23:23:05 by art3mis           #+#    #+#             */
/*   Updated: 2024/09/25 19:36:19 by annabrag         ###   ########.fr       */
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
	t_exec_lst		exec;

	head = t;
	ft_bzero(&exec, sizeof(exec));
	while (head != NULL)
	{
		if (head->prev != NULL)
			head->type = __classify(head->content, head->prev->content);
		else
			head->type = __classify(head->content, NULL);
		if (head->type == HERE_DOC)
			exec.heredoc_nb++;
		printf(BOLD CYAN "token_type:\t %d\n" R, head->type);
		head = head->next;
	}
	printf("heredoc count: %d\n", exec.heredoc_nb);
}
