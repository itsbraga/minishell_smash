/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_token_lst.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: annabrag <annabrag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 22:48:25 by art3mis           #+#    #+#             */
/*   Updated: 2024/09/11 20:34:44 by annabrag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	create_token_lst(t_main_lst *main, t_token_lst *t)
{
	t_token_lst		*new_node;
	t_token_type	type;
	t_classifier	c;

	while (main != NULL)
	{
		c.seg_elems = ft_split(main->content, ' ');
		if (c.seg_elems == NULL)
			return (FAILURE);
		c.i = 0;
		while (c.seg_elems[c.i] != NULL)
		{
			type = classify_token(&c);
			new_node = token_lst_new_node(c.seg_elems[c.i], type);
			if (new_node == NULL)
			{
				free_tab(c.seg_elems);
				return (err_msg("malloc", ERR_MALLOC, 0), FAILURE);
			}
			token_lst_add_back(&t, new_node);
			c.i++;
		}
		main = main->next;
		free_tab(c.seg_elems);
	}
	return (SUCCESS);
}

// int	create_token_lst(t_main_lst *main, t_token_lst *t)
// {
// 	t_token_lst		*new_node;
// 	t_classifier	c;

// 	while (main != NULL)
// 	{
// 		c.seg_elems = ft_split(main->content, ' ');
// 		if (c.seg_elems == NULL)
// 			return (FAILURE);
// 		c.i = 0;
// 		while (c.seg_elems[c.i] != NULL)
// 		{
// 			new_node = token_lst_new_node(c.seg_elems[c.i], classify_token(&c));
// 			if (new_node == NULL)
// 			{
// 				free_tab(c.seg_elems);
// 				return (err_msg("malloc", ERR_MALLOC, 0), FAILURE);
// 			}
// 			token_lst_add_back(&t, new_node);
// 			c.i++;
// 		}
// 		main = main->next;
// 		free_tab(c.seg_elems);
// 	}
// 	return (SUCCESS);
// }
