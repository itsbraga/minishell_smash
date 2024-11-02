/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_token_dblst.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: art3mis <art3mis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 22:48:25 by art3mis           #+#    #+#             */
/*   Updated: 2024/11/02 02:10:34 by art3mis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser_lexer.h"

static char	**__get_all_seg_elems(char *main_content)
{
	t_token_parser	p;
	size_t			seg_len;

	if (main_content == NULL || main_content[0] == '\0')
		return (NULL);
	ft_bzero(&p, sizeof(t_token_parser));
	p.main_content = main_content;
	seg_len = ft_strlen(p.main_content);
	p.seg_elems = yama(CREATE_TAB, NULL, (sizeof(char *) * (seg_len + 1)));
	secure_malloc(p.seg_elems, true);
	while (p.main_content[p.i] != '\0')
		parse_segment(&p);
	p.seg_elems[p.token_count] = NULL;
	return (p.seg_elems);
}

int	create_token_dblst(t_data *d)
{
	t_main_lst		*curr;
	t_token_dblst	*new_token;
	char			**seg_elems;

	curr = d->main;
	while (curr != NULL)
	{
		seg_elems = __get_all_seg_elems(curr->content);
		if (seg_elems == NULL)
			return (FAILURE);
		lstclear_token(&(d->token));
		while (*seg_elems != NULL)
		{
			new_token = token_dblst_new_node(*seg_elems, UNKNOWN);
			secure_malloc(new_token, true);
			token_dblst_add_back(&(d->token), new_token);
			seg_elems++;
		}
		lst_tokenization(d->token);
		if (create_exec_lst(d) == FAILURE)
			return (FAILURE);
		curr = curr->next;
	}
	return (SUCCESS);
}
