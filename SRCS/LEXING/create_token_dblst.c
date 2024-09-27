/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_token_dblst.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: art3mis <art3mis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 22:48:25 by art3mis           #+#    #+#             */
/*   Updated: 2024/09/27 02:52:46 by art3mis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**__get_all_seg_elems(t_main_lst *main)
{
	t_token_parser	p;
	size_t			seg_len;
	
	ft_bzero(&p, sizeof(p));
	p.main = main;
	if (p.main == NULL || p.main->content == NULL)
		return (NULL);
	seg_len = ft_strlen(main->content);
	p.seg_elems = yama(CREATE_TAB, NULL, (sizeof(char *) * (seg_len + 1)));
	if (p.seg_elems == NULL)
		(err_msg("malloc", ERR_MALLOC, 0), clean_exit_shell(FAILURE));
	while (p.main->content[p.i] != '\0')
		parse_segment(&p);
	p.seg_elems[p.token_count] = NULL;
	return (p.seg_elems);
}

int	create_token_dblst(t_data *d)
{
	t_token_dblst	*new_token;
	char			**seg_elems;

	while (d->main != NULL)
	{
		lstclear_token(&(d->token));
		seg_elems = __get_all_seg_elems(d->main);
		if (seg_elems == NULL)
			return (err_msg("malloc", ERR_MALLOC, 0), FAILURE);
		while (*seg_elems != NULL)
		{
			new_token = token_dblst_new_node(*seg_elems, UNKNOWN);
			if (new_token == NULL)
				(err_msg("malloc", ERR_MALLOC, 0), clean_exit_shell(FAILURE));
			(void)yama(ADD, new_token, 0);
			token_dblst_add_back(&(d->token), new_token);
			seg_elems++;
		}
		lst_tokenization(d->token);
		display_token_dblst(d->token);
		if (create_redir_lst(&(d->exec->redir), d->token) == FAILURE)
			return (err_msg(NULL, "could not create redir_lst", 0), FAILURE);
		d->main = d->main->next;
	}
	return (SUCCESS);
}
