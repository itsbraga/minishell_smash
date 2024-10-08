/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_token_dblst.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: annabrag <annabrag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 22:48:25 by art3mis           #+#    #+#             */
/*   Updated: 2024/10/08 17:03:06 by annabrag         ###   ########.fr       */
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
	secure_malloc(p.seg_elems);
	while (p.main->content[p.i] != '\0')
	{
		if (check_redir_sequence(p.main->content) == FAILURE)
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
		lstclear_token(&(d->token));
		seg_elems = __get_all_seg_elems(d->main);
		secure_malloc2(seg_elems, false);
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
			return (err_msg(NULL, "could not create exec_lst", 0), FAILURE);
		printf("heredoc count: %d\n", d->exec->heredoc_nb);
		d->exec->heredoc_nb = 0;
		d->main = d->main->next;
	}
	// lstclear_exec(&(d->exec));
	return (SUCCESS);
}
