/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_dblst.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: art3mis <art3mis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 23:02:40 by art3mis           #+#    #+#             */
/*   Updated: 2024/09/27 01:07:05 by art3mis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token_dblst	*token_dblst_new_node(char *content, t_token_type type)
{
	t_token_dblst	*new_node;
	
	new_node = yama(CREATE, NULL, sizeof(t_token_dblst));
	if (new_node == NULL)
	{
		err_msg("malloc", ERR_MALLOC, 0);
		clean_exit_shell(FAILURE);
	}
	new_node->exec = NULL;
    new_node->type = type;
	new_node->content = ft_strdup(content);
    if (new_node->content == NULL)
	{
		err_msg("malloc", ERR_MALLOC, 0);
		clean_exit_shell(FAILURE);
	}
	(void)yama(ADD, new_node->content, 0);
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
	t_token_dblst	*head;

	size = 0;
	head = *t;
	while (head != NULL)
	{
		size++;
		head = head->next;
	}
	return (size);
}

void	del_current_token(t_token_dblst **t, t_token_dblst *to_delete)
{
	if (t == NULL || (*t) == NULL || to_delete == NULL)
		return ;
	if (*t == to_delete)	// cas ou to_delete est le premier noeud
	{
		*t = to_delete->next;	// le suivant devient la nouvelle tete de liste
		if (*t != NULL)
			(*t)->prev = NULL;	// si la liste n'est pas vide, on met a jour le precedent
	}
	else // cas ou to_delete est au milieu / a la fin
	{
		if (to_delete->prev != NULL)
			to_delete->prev->next = to_delete->next; // le next du prev devient le next du noeud supprime
		if (to_delete->next != NULL)
			to_delete->next->prev = to_delete->prev; // le prev du next devient le prev du noeud supprime
	}
	free(to_delete->content);
	free(to_delete);
}
