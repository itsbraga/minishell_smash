/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_token_lst.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: art3mis <art3mis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 22:48:25 by art3mis           #+#    #+#             */
/*   Updated: 2024/09/10 19:05:24 by art3mis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_sub_lst	*__ll_container_new_node(t_token *token)
{
	t_sub_lst	*new_container;
	
	new_container = malloc(sizeof(t_sub_lst));
	if (new_container == NULL)
		return (NULL);
	new_container->head_token = token;
	new_container->next = NULL;
	return (new_container);
}

int	create_token_lst(t_main_lst *main, t_token *t)
{
	t_sub_lst		*new_token_lst;
	t_token			*new_node;
	t_classifier	c;

	while (main != NULL)
	{
		c.elems = ft_split(main->content, ' ');
		if (c.elems == NULL)
			return (FAILURE);
		c.i = 0;
		while (c.elems[c.i] != NULL)
		{
			new_node = token_lst_new_node(c.elems[c.i]);
			if (new_node == NULL)
				return (free_tab(c.elems), err_msg("malloc", ERR_MALLOC, 0), 1);
			if (classify_token(&c) != SUCCESS)
				return (free_tab(c.elems), 1);
			token_lst_add_back(&c.token_lst, new_node);
			c.i++;
		}
		new_token_lst = __ll_container_new_node(c.token_lst);
		// ajouter les tokens a t_token dans t_global
		main = main->next;
		free_tab(c.elems);
	}
	return (SUCCESS);
}
