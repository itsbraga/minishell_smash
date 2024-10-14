/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_token_dblst.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: annabrag <annabrag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 22:48:25 by art3mis           #+#    #+#             */
/*   Updated: 2024/10/14 19:52:04 by annabrag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**__get_all_seg_elems(char *main_content)
{
	t_token_parser	p;
	size_t			seg_len;

	ft_bzero(&p, sizeof(p));
	p.main_content = main_content;
	if (p.main_content == NULL || p.main_content[0] == '\0')
		return (NULL);
	seg_len = ft_strlen(main_content);
	p.seg_elems = yama(CREATE_TAB, NULL, (sizeof(char *) * (seg_len + 1)));
	secure_malloc(p.seg_elems);
	while (p.main_content[p.i] != '\0')
	{
		if (check_redir_sequence(p.main_content) == FAILURE)
			return (NULL);
		parse_segment(&p);
	}
	p.seg_elems[p.token_count] = NULL;
	return (p.seg_elems);
}

int	create_token_dblst(t_data *d)
{
	t_token_dblst	*new_token;
	char			**seg_elems;
	int				i;

	while (d->main != NULL)
	{
		seg_elems = __get_all_seg_elems(d->main->content);
		secure_malloc(seg_elems);
		lstclear_token(&(d->token));
		(void)yama(ADD, seg_elems, 0);
		i = 0;
		while (seg_elems[i] != NULL)
		{
			new_token = token_dblst_new_node(seg_elems[i], UNKNOWN);
			secure_malloc(new_token);
			(void)yama(ADD, new_token, 0);
			token_dblst_add_back(&(d->token), new_token);
			i++;
		}
		lst_tokenization(d->token);
		display_token_dblst(d->token);
		if (create_exec_lst(d) == FAILURE)
			return (FAILURE);
		d->main = d->main->next;
	}
	printf("11 FINISHED t_token_dblst creation\n");
	(void)yama(REMOVE, seg_elems, 0);
	return (SUCCESS);
}
