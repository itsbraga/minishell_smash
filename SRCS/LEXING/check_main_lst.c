/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_main_lst.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: annabrag <annabrag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 22:56:00 by art3mis           #+#    #+#             */
/*   Updated: 2024/09/25 21:42:29 by annabrag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	__take_seg_elem(t_token_parser *p)
{
	char    *tmp;

	tmp = NULL;
	if (p->i > p->start)
	{
		tmp = ft_strldup(p->main->content + p->start, (p->i - p->start));
		if (tmp == NULL)
			(err_msg("malloc", ERR_MALLOC, 0), clean_exit_shell(FAILURE));
		(void)yama(ADD, tmp, 0);
		p->seg_elems[p->token_count++] = tmp;
	}
}

static void	__init(t_token_parser *p)
{
	p->closed_quotes[0] = true;
	p->closed_quotes[1] = true;
	p->i = 0;
	p->start = p->i;
}

static void	__get_closed_quotes(t_token_parser *p)
{
	if (p->main->content[p->i] == '\'')
		p->closed_quotes[0] = switch_bool(p->closed_quotes[0]);
	else if (p->main->content[p->i] == '"')
		p->closed_quotes[1] = switch_bool(p->closed_quotes[1]);
}

bool	is_redir(t_token_parser *p)
{
	if (p->main->content[p->i] == REDIR_IN || p->main->content[p->i] == HERE_DOC
		|| p->main->content[p->i] == REDIR_OUT_TRUNC
		|| p->main->content[p->i] == REDIR_OUT_APPEND)
		return (true);
	return (false);
}

static void __parse_segment(t_token_parser *p)
{
	__init(p);
	while (p->main->content[p->i] != '\0')
	{
		__get_closed_quotes(p);
		if (p->main->content[p->i] == ' ' && p->closed_quotes[0] == true && p->closed_quotes[1] == true)
        {
            __take_seg_elem(p);
            while (ft_isspace(p->main->content[p->i]) == 1)
                p->i++;
            p->start = p->i; // Redéfinir le début pour le prochain token
        }
        else
            p->i++;
		if (p->main->content[p->i] == '\0' && (p->i > p->start))
			__take_seg_elem(p);
	}
}

char	**get_all_seg_elems(t_main_lst *main)
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
		__parse_segment(&p);
	p.seg_elems[p.token_count] = NULL;
	return (p.seg_elems);
}
