/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_token_dblst.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: art3mis <art3mis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 22:48:25 by art3mis           #+#    #+#             */
/*   Updated: 2024/09/24 01:18:10 by art3mis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**__split_main_content(t_main_lst *main)
{
	t_token_parser	p;

	ft_bzero(&p, sizeof(p));
	p.main = main;
	if (p.main == NULL || p.main->content == NULL)
		return (NULL);
	if (ft_strchr(p.main->content, '\'') != NULL
		|| ft_strchr(p.main->content, '"') != NULL)
	{
		p.seg_elems = get_quoted_seg_elems(p.main, &p);
		if (p.seg_elems == NULL)
			return (err_msg("malloc", ERR_QUOTES, 0), NULL);
	}
	else
	{
		p.seg_elems = ft_split(p.main->content, ' ');
		if (p.seg_elems == NULL)
			(err_msg("malloc", ERR_MALLOC, 0), clean_exit_shell(FAILURE));
		(void)yama(ADD, p.seg_elems, 0);
	}
	return (p.seg_elems);
}

int	create_token_dblst(t_main_lst *main, t_exec_lst *exec)
{
	t_token_dblst	*new_token;
	char			**seg_elems;

	while (main != NULL)
	{
		main->tokens = NULL;
		seg_elems = __split_main_content(main);
		if (seg_elems == NULL)
			return (err_msg("malloc", ERR_MALLOC, 0), FAILURE);
		while (*seg_elems != NULL)
		{
			new_token = token_dblst_new_node(*seg_elems, -1);
			printf(BOLD BLUE "new_tok:\t |%s|\n" RESET, new_token->content);
			if (new_token == NULL)
				(err_msg("malloc", ERR_MALLOC, 0), clean_exit_shell(FAILURE));
			(void)yama(ADD, new_token, 0);
			token_dblst_add_back(&main->tokens, new_token);
			seg_elems++;
		}
		lst_tokenization(main->tokens, exec);
		main = main->next;
	}
	return (SUCCESS);
}
