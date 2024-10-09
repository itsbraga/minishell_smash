/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_lst_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: annabrag <annabrag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 12:34:57 by art3mis           #+#    #+#             */
/*   Updated: 2024/10/09 21:31:41 by annabrag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	__has_quotes(char *content)
{
	int	i;

	i = 0;
	while (content[i] != '\0')
	{
		if (content[i] == '"' || content[i] == '\'')
			return (true);
		i++;
	}
	return (false);
}

char	*token_cleanup(char *content)
{
	if (__has_quotes(content) == false)
		return (content);
	content = empty_quotes(content);
	content = expand(data_struct(), content, false);
	content = other_quotes(content);
	return (content);
}

int	cmd_token_count(t_token_dblst *t)
{
	int	count;

	count = 0;
	while (t != NULL)
	{
		if (t->type == COMMAND || t->type == WORD)
			count++;
		t = t->next;
	}
	return (count);
}
