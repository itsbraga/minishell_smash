/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_lst_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: annabrag <annabrag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 12:34:57 by art3mis           #+#    #+#             */
/*   Updated: 2024/10/31 11:13:40 by annabrag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser_lexer.h"

void	init_ptrs(t_ptrs *p)
{
	p->new_task = NULL;
	p->i = 0;
}

char	*token_cleanup(char *content)
{
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
