/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mainbis.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: annabrag <annabrag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 21:59:47 by pmateo            #+#    #+#             */
/*   Updated: 2024/08/26 15:39:04 by annabrag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../INCLUDES/mini_parsing.h"

t_token	*last_node(t_token *t)
{
	if (!t)
		return (NULL);
	while (t->next != NULL)
		t = t->next;
	return (t);
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

t_token	*new_node(char *content)
{
	t_token	*new_node;
	
	new_node = malloc(sizeof(t_token));
	if (!new_node)
		return (NULL);
	new_node->idx = 0;
	new_node->to_expand = false;
	new_node->content = content;
	new_node->next = NULL;
	return (new_node);
}

size_t	get_tlist_size(t_token **t)
{
	size_t	size;
	t_token *current;

	size = 0;
	current = *t;
	while (current != NULL)
	{
		size++;
		current = current->next;
	}
	return(size);
}

int	main(void)
{
	t_token *t;
	// int i = 4;
	t_token *cell;
	t_token *cell1;
	t_token *cell2;
	t_token *cell3;
	char content[7] = "content";	
	
	t = NULL;
	cell = new_node(content);
	if (!cell)
		return (EXIT_FAILURE);
	cell1 = new_node(content);
	cell2 = new_node(content);
	cell3 = new_node(content);
	add_back(&t, cell);
	add_back(&t, cell1);
	add_back(&t, cell2);
	add_back(&t, cell3);
	// while (i)
	// {
	// 	add_back(&t, cell);
	// 	i--;	
	// }
	ft_printf(1 ,"size = %i\n", get_tlist_size(&t));
}