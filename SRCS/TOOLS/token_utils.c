/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmateo <pmateo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 15:58:33 by annabrag          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2024/08/26 16:54:29 by annabrag         ###   ########.fr       */
=======
<<<<<<< HEAD
/*   Updated: 2024/08/26 16:11:25 by pmateo           ###   ########.fr       */
=======
/*   Updated: 2024/08/26 15:39:04 by annabrag         ###   ########.fr       */
>>>>>>> 6e6a8733545fee32380e072c25f1579acc0c37b4
>>>>>>> 331b04d903f2a2b001b4dd4fcb2fdae6e653d3e1
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*new_node(char *content)
{
	t_token	*new_node;
	
	new_node = malloc(sizeof(t_token));
	if (new_node == NULL)
		return (NULL);
	new_node->content = content;
	new_node->next = NULL;
	return (new_node);
}

t_token	*last_node(t_token *t)
{
	if (t == NULL)
		return (NULL);
	while (t->next != NULL)
		t = t->next;
	return (t);
}

void	add_back(t_token **t, t_token *new_node)
{
	t_token	*tmp;

	if ((*t) == NULL)
		*t = new_node;
	else
	{
		tmp = last_node(*t);
		tmp->next = new_node;
	}
}

size_t	get_tlist_size(t_token **t)
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

void	display_tokens(t_token *t)
{
	t_token	*tmp;

	tmp = t;
	while (tmp != NULL)
	{
		ft_putstr_fd(tmp->content, 1);
		ft_putendl_fd("", 1);
		tmp = tmp->next;
	}
}
