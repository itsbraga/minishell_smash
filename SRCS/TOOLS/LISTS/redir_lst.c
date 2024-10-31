/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_lst.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: annabrag <annabrag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 21:06:09 by art3mis           #+#    #+#             */
/*   Updated: 2024/10/23 21:54:01 by annabrag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tools.h"

t_redir_lst	*redir_lst_new_node(t_token_type type)
{
	t_redir_lst	*new_node;

	new_node = malloc(sizeof(t_redir_lst));
	secure_malloc(new_node, true);
	new_node->type = type;
	new_node->limiter = NULL;
	new_node->infile = NULL;
	new_node->outfile = NULL;
	new_node->next = NULL;
	return (new_node);
}

static t_redir_lst	*__redir_lst_last_node(t_redir_lst *r)
{
	if (r == NULL)
		return (NULL);
	while (r->next != NULL)
		r = r->next;
	return (r);
}

void	redir_lst_add_back(t_redir_lst **r, t_redir_lst *new_node)
{
	t_redir_lst	*tmp;

	if ((*r) == NULL)
		*r = new_node;
	else
	{
		tmp = __redir_lst_last_node(*r);
		tmp->next = new_node;
	}
}

size_t	get_redir_lst_size(t_redir_lst **r)
{
	size_t		size;
	t_redir_lst	*curr;

	size = 0;
	curr = *r;
	while (curr != NULL)
	{
		size++;
		curr = curr->next;
	}
	return (size);
}

bool	is_redir(char *str)
{
	return (*str == '<' || *str == '>');
}
