/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_token_dblst.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: art3mis <art3mis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 22:48:25 by art3mis           #+#    #+#             */
/*   Updated: 2024/09/16 01:07:27 by art3mis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	create_token_dblst(t_main_lst *main, t_token_dblst **t)
{
	t_token_dblst	*new_node;
	char			**seg_elems;
	size_t			i;

	lstclear_tokens(t);
	seg_elems = split_main_content(main);
	if (seg_elems == NULL)
		return (FAILURE);
	i = 0;
	while (seg_elems[i] != NULL)
	{
		new_node = token_dblst_new_node(seg_elems[i], -1);
		if (new_node == NULL)
		{
			// free_tab(seg_elems);
			return (err_msg("malloc", ERR_MALLOC, 0), FAILURE);
		}
		token_dblst_add_back(t, new_node);
		i++;
	}
	free_tab(seg_elems);
	lst_tokenization(*t);
	return (SUCCESS);
}
