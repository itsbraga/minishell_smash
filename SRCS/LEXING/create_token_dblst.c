/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_token_dblst.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: annabrag <annabrag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 22:48:25 by art3mis           #+#    #+#             */
/*   Updated: 2024/09/18 17:45:18 by annabrag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	create_token_dblst(t_main_lst *main)
{
	t_token_dblst	*new_token;
	char			**seg_elems;

	while (main != NULL)
	{
		main->tokens = NULL;
		// lstclear_tokens(&main->tokens);
		seg_elems = split_main_content(main);
		if (seg_elems == NULL)
			return (err_msg("malloc", ERR_MALLOC, 0), FAILURE);
		(void)yama(ADD, seg_elems, 0); // verifier si ici ou dans la fonc elle meme
		while (*seg_elems != NULL)
		{
			new_token = token_dblst_new_node(*seg_elems, -1);
			printf("new_tok: %s\n", new_token->content);
			if (new_token == NULL)
				return (err_msg("malloc", ERR_MALLOC, 0), FAILURE);
			(void)yama(ADD, new_token, 0);
			token_dblst_add_back(&main->tokens, new_token);
			seg_elems++;
		}
		lst_tokenization(main->tokens);
		main = main->next;
	}
	return (SUCCESS);
}
