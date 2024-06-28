/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   del_token.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: annabrag <annabrag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 19:35:38 by annabrag          #+#    #+#             */
/*   Updated: 2024/06/28 19:53:37 by annabrag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../INCLUDES/minishell.h"

void	clear_tokens(t_token **t)
{
	t_token	*tmp;
	t_token	*new_next;
	
	if (!t)
		return ;
	tmp = *t;
	while (tmp != NULL)
	{
		new_next = tmp->next;
		delone_token(tmp);
		tmp = new_next;
	}
	tmp = NULL;
}

void	delone_token(t_token *t)
{
	if (t->content != NULL)
		free(t->content);
	free(t);
}

void	delcurrent_token(t_token **t, t_token *cur)
{
	t_token	*prev;
	t_token	*tmp;

	if (!t || !(*t) || !cur)
		return ;
	prev = NULL;
	tmp = *t;
	if (*t == cur)
	{
		*t = cur->next;
		delone_token(cur);
		return ;
	}
	while (tmp != NULL && tmp != cur)
	{
		prev = tmp;
		tmp = tmp->next;
	}
	if (!tmp)
		return ;
	else if (prev != NULL)
		prev->next = cur->next;
	delone_token(cur);
}
