/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_dblst.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: art3mis <art3mis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 23:02:40 by art3mis           #+#    #+#             */
/*   Updated: 2024/11/02 03:06:55 by art3mis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tools.h"

t_token_dblst	*token_dblst_new_node(char *content, t_token_type type)
{
	t_token_dblst	*new_node;

	new_node = malloc(sizeof(t_token_dblst));
	secure_malloc(new_node, true);
	new_node->type = type;
	new_node->content = ft_strdup(content);
	secure_malloc(new_node->content, true);
	new_node->prev = NULL;
	new_node->next = NULL;
	return (new_node);
}

static t_token_dblst	*__token_dblst_last_node(t_token_dblst *t)
{
	if (t == NULL)
		return (NULL);
	while (t->next != NULL)
		t = t->next;
	return (t);
}

void	token_dblst_add_back(t_token_dblst **t, t_token_dblst *new_node)
{
	t_token_dblst	*tmp;

	if ((*t) == NULL)
		*t = new_node;
	else
	{
		tmp = __token_dblst_last_node(*t);
		tmp->next = new_node;
		new_node->prev = tmp;
	}
}

size_t	get_token_dblst_size(t_token_dblst **t)
{
	size_t			size;
	t_token_dblst	*curr;

	size = 0;
	curr = *t;
	while (curr != NULL)
	{
		size++;
		curr = curr->next;
	}
	return (size);
}

void	del_current_token(t_token_dblst **t, t_token_dblst *to_delete)
{
	if (t == NULL || (*t) == NULL || to_delete == NULL)
		return ;
	if (*t == to_delete)
	{
		*t = to_delete->next;
		if (*t != NULL)
			(*t)->prev = NULL;
	}
	else
	{
		if (to_delete->prev != NULL)
			to_delete->prev->next = to_delete->next;
		if (to_delete->next != NULL)
			to_delete->next->prev = to_delete->prev;
	}
	free_and_set_null((void **)&to_delete->content);
	free_and_set_null((void **)&to_delete);
}
