/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_lst_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: art3mis <art3mis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 12:34:57 by art3mis           #+#    #+#             */
/*   Updated: 2024/10/22 21:07:24 by art3mis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing-lexing.h"

void	init_ptrs(t_ptrs *p)
{
	p->new_task = NULL;
	p->i = 0;
}

char	*token_cleanup(char *content)
{
	t_data	*d;

	d = data_struct();
	content = empty_quotes(content);
	content = expand(d, content, false);
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
