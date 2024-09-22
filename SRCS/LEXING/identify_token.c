/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   identify_token.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: annabrag <annabrag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 23:23:05 by art3mis           #+#    #+#             */
/*   Updated: 2024/09/22 21:41:50 by annabrag         ###   ########.fr       */
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
	else if (ft_strcmp(token, "<") == 0)
		return (REDIR_IN);
	else if (ft_strcmp(token, "<<") == 0)
		return (HERE_DOC);
	else if (ft_strcmp(token, ">") == 0)
		return (REDIR_OUT_TRUNC);
	else if (ft_strcmp(token, ">>") == 0)
		return (REDIR_OUT_APPEND);
	else if (prev == NULL || ft_strcmp(prev, "|") == 0)
		return (COMMAND);
	// if prev->type == COMMAND --> ARGUMENT
	return (WORD);
}

// static t_token_type	__classify_quoted_token(char *token, char *prev)
// {
// 	char			*cleaned_token;
// 	t_token_type	type;

// 	cleaned_token = ft_strtrim(token, "'\"");
// 	if (cleaned_token == NULL)
// 		(err_msg("malloc", ERR_MALLOC, 0), clean_exit_shell(FAILURE));
// 	(void)yama(ADD, cleaned_token, 0);
// 	type = __classify(cleaned_token, prev);
// 	free(cleaned_token);
// 	return (type);
// }

void	lst_tokenization(t_token_dblst *t, t_exec_lst *exec)
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
		{
			exec->heredoc_nb++;
			printf("heredoc count: %d\n", exec->heredoc_nb);
		}
		printf("type:\t\t %d\n", head->type);
		head = head->next;
	}
}
