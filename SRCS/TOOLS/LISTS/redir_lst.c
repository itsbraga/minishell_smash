/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_lst.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: art3mis <art3mis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 21:06:09 by art3mis           #+#    #+#             */
/*   Updated: 2024/10/11 23:14:12 by art3mis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_redir_lst	*redir_lst_new_node(t_token_type type)
{
	t_redir_lst	*new_node;

	new_node = yama(CREATE, NULL, sizeof(t_redir_lst));
	secure_malloc(new_node);
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
	{
		*r = new_node;
		printf("FIRST node type : %d, located at %p\n", (*r)->type, (*r));
	}
	else
	{
		tmp = __redir_lst_last_node(*r);
		tmp->next = new_node;
		printf("last_node type : %d, located at %p\n", tmp->type, tmp);
		printf("new_node type : %d, located at %p\n", tmp->next->type, tmp->next);
	}
}

size_t	get_redir_lst_size(t_redir_lst **r)
{
	size_t		size;
	t_redir_lst	*current;

	size = 0;
	current = *r;
	while (current != NULL)
	{
		size++;
		current = current->next;
	}
	return (size);
}

bool	is_redir(char *str)
{
	return (*str == '<' || *str == '>');
}
