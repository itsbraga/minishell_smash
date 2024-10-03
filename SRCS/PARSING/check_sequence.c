/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_sequence.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: art3mis <art3mis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 18:36:43 by art3mis           #+#    #+#             */
/*   Updated: 2024/10/03 23:05:28 by art3mis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// int	check_redir_sequence(t_token_dblst *t)
// {
// 	t_token_dblst   *head;

// 	head = t;
// 	while (head != NULL)
// 	{
// 		if (IS_REDIR(head->type) == true)
// 		{
// 			if (head->next == NULL)
// 			{
// 				err_msg(NULL, "newline", 2);
// 				return (FAILURE);
// 			}
// 		}
// 		head = head->next;
// 	}
// 	return (SUCCESS);
// }

int check_redir_sequence(char *content)
{
	int	i;

	i = 0;
	while (content[i] != '\0')
	{
		if (content[i] == '<' || ft_strcmp(content, "<<") == 0
			|| content[i] == '>' || ft_strcmp(content, ">>") == 0)
		{
			if (content[i + 1] == '\0' || content[i + 1] == '|'
				|| content[i + 2] == '|')
			{
				err_msg(NULL, "newline", 2);
				return (FAILURE);
			}
		}
		i++;
	}
	return (SUCCESS);
}
