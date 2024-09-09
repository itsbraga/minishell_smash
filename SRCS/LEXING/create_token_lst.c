/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_token_lst.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: art3mis <art3mis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 22:48:25 by art3mis           #+#    #+#             */
/*   Updated: 2024/09/10 01:31:45 by art3mis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	create_token_lst(t_main_lst *main)
{
	t_token			*new_node;
	t_classifier	c;
	bool			is_command;

	while (main != NULL)
	{
		c.elems = ft_split(main->content, ' ');
		if (c.elems == NULL)
			return (FAILURE);
		c.head_token_lst = NULL;
		c.i = 0;
		is_command = true; // on part du principe ou le premier est une cmd
		while (c.elems[c.i] != NULL)
		{
			new_node = token_lst_new_node(c.elems[c.i]);
			if (new_node == NULL)
			{
				free_tab(c.elems);
				return (err_msg("malloc", ERR_MALLOC, 0), FAILURE);
			}
			if (classify_token(&c, &is_command) != SUCCESS)
				return (free_tab(c.elems), FAILURE);
			token_lst_add_back(&c.head_token_lst, new_node);
			c.i++;
		}
		main = main->next;
		free_tab(c.elems);
	}
	return (SUCCESS);
}
