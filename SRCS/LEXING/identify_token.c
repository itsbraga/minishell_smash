/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   identify_token.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: annabrag <annabrag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 23:23:05 by art3mis           #+#    #+#             */
/*   Updated: 2024/09/18 17:35:47 by annabrag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// 
// Ne gere pas le cas ou le prev de la COMMAND est un INFILE: erreur
// 
// static t_token_type	__classify(char *token, char *prev, char *pprev)
// {
// 	if (ft_strcmp(token, "<") == 0)
// 		return (REDIR_IN);
// 	else if (ft_strcmp(token, "<<") == 0)
// 		return (HERE_DOC);
// 	else if (ft_strcmp(token, ">") == 0)
// 		return (TRUNC);
// 	else if (ft_strcmp(token, ">>") == 0)
// 		return (APPEND);
// 	else if (prev != NULL)
// 	{
// 		if (ft_strcmp(prev, "<") == 0)
// 			return (INFILE);
// 		else if (ft_strcmp(prev, "<<") == 0)
// 			return (LIMITER);
// 		else if (ft_strcmp(prev, ">") == 0 || ft_strcmp(prev, ">>") == 0)
// 			return (OUTFILE);
// 	}
// 	else if (ft_strchr(token, '"') != NULL || ft_strchr(token, '\'') != NULL)
// 		return (IN_QUOTE);
// 	else if (prev == NULL || ft_strcmp(prev, "|") == 0 || ft_strcmp(pprev, "<") == 0)
// 		return (COMMAND);
// 	return (ARGUMENT);
// }

// void	lst_tokenization(t_token_dblst *t)
// {
// 	t_token_dblst	*head;

// 	head = t;
// 	while (head != NULL)
// 	{
// 		if (head->prev != NULL)
// 		{
// 			head->type = __classify(head->content, head->prev->content, NULL);
// 			printf("prev:\t %s\n", head->prev->content);
// 			printf("type:\t %d\n", head->type);
// 			if (head->prev->prev != NULL)
// 			{
// 				head->type = __classify(head->content, head->prev->content, head->prev->prev->content);
// 				printf("2: prev->prev:\t %s\n", head->prev->prev->content);
// 				printf("2: type:\t %d\n", head->type);
// 			}
// 		}
// 		else
// 		{
// 			head->type = __classify(head->content, NULL, NULL);
// 			printf("type:\t %d\n", head->type);
// 		}
// 		head = head->next;
// 	}
// }

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

void	lst_tokenization(t_token_dblst *t)
{
	t_token_dblst	*head;

	head = t;
	while (head != NULL)
	{
		if (head->prev != NULL)
		{
			head->type = __classify(head->content, head->prev->content);
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
