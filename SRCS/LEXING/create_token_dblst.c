/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_token_dblst.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: art3mis <art3mis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 22:48:25 by art3mis           #+#    #+#             */
/*   Updated: 2024/09/24 21:44:01 by art3mis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	create_token_dblst(t_main_lst *main)
{
	t_token_dblst	*new_token;
	char			**seg_elems;
	t_redir_lst		*redirs;

	redirs = NULL;
	while (main != NULL)
	{
		main->tokens = NULL;
		seg_elems = get_all_seg_elems(main);
		if (seg_elems == NULL)
			return (err_msg("malloc", ERR_MALLOC, 0), FAILURE);
		while (*seg_elems != NULL)
		{
			new_token = token_dblst_new_node(*seg_elems, -1);
			printf(BLUE "new_token:\t [" R "%s" BLUE "]\n" R, new_token->content);
			if (new_token == NULL)
				(err_msg("malloc", ERR_MALLOC, 0), clean_exit_shell(FAILURE));
			(void)yama(ADD, new_token, 0);
			token_dblst_add_back(&main->tokens, new_token);
			seg_elems++;
		}
		lst_tokenization(main->tokens);
		fill_redir_lst(main->tokens, &redirs);
		main = main->next;
	}
	return (SUCCESS);
}
