/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: annabrag <annabrag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 15:58:33 by annabrag          #+#    #+#             */
/*   Updated: 2024/06/28 17:40:34 by annabrag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../INCLUDES/minishell.h"

t_token	*new_node(char *content)
{
	t_token	*new_node;
	
	new_node = malloc(sizeof(t_token));
	if (!new_node)
		return (NULL);
	new_node->idx = 0;
	new_node->to_expand = false;
	new_node->s_quoted = false;
	new_node->d_quoted = false;
	new_node->t_quoted = 0;
	new_node->content = content;
	new_node->next = NULL;
	return (new_node);
}

t_token	*last_node(t_token *t)
{
	if (!t)
		return (NULL);
	else
	{
		while (t->next != NULL)
			t = t->next;
		return (t);
	}
}

void	add_back(t_token **t, t_token *new_node)
{
	t_token	*tmp;

	if (!(*t))
		*t = new_node;
	else
	{
		tmp = last_node(*t);
		tmp->next = new_node;
	}
}

void	clear_lst(t_token **t)
{
	t_token	*cur;
	t_token	*new_next;
	
	cur = *t;
	while (cur != NULL)
	{
		new_next = cur->next;
		free(cur);
		cur = new_next;
	}
	*t = NULL;
}

void	del_one(t_token *t)
{
	if (t->content != NULL)
		free(t->content);
	free(t);
	//faire pointer sur la cellule suivante, ne pas laisser de trou
}
