/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_lst_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: art3mis <art3mis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 23:02:40 by art3mis           #+#    #+#             */
/*   Updated: 2024/09/10 00:20:46 by art3mis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*token_lst_new_node(char *content)
{
	t_token	*new_node;
	
	new_node = malloc(sizeof(t_token));
	if (new_node == NULL)
		return (NULL);
    // new_node->type = type;
	new_node->content = ft_strdup(content);
    if (new_node->content == NULL)
    {
        free(new_node);
        return (NULL);
    }
	new_node->next = NULL;
	return (new_node);
}

static t_token	*__token_lst_last_node(t_token *t)
{
	if (t == NULL)
		return (NULL);
	while (t->next != NULL)
		t = t->next;
	return (t);
}

void	token_lst_add_back(t_token **t, t_token *new_node)
{
	t_token	*tmp;

	if ((*t) == NULL)
		*t = new_node;
	else
	{
		tmp = __token_last_node(*t);
		tmp->next = new_node;
	}
}

size_t	get_token_lst_size(t_token **t)
{
	size_t	size;
	t_token *node;

	size = 0;
	node = *t;
	while (node != NULL)
	{
		size++;
		node = node->next;
	}
	return (size);
}

void	del_current_token(t_token **t, t_token *cur)
{
	t_token	*prev;
	t_token	*tmp;

	if (t == NULL || (*t) == NULL || cur == NULL)
		return ;
	prev = NULL;
	tmp = *t;
	if (*t == cur)
	{
		*t = cur->next;
		free(cur->content);
		free(cur);
		return ;
	}
	while (tmp != NULL && tmp != cur)
	{
		prev = tmp;
		tmp = tmp->next;
	}
	if (tmp == NULL)
		return ;
	prev->next = cur->next;
	free(cur->content);
	free(cur);
}
