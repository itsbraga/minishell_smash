/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_main_lst.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: art3mis <art3mis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 22:56:00 by art3mis           #+#    #+#             */
/*   Updated: 2024/09/24 01:22:08 by art3mis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	__take_seg_elem(t_token_parser *p)
{
	char    *tmp;

	tmp = NULL;
	if (p->i > p->start)
	{
		if (p->main->content[p->i] == '\'' || p->main->content[p->i] == '"')
		{
			tmp = ft_strldup(p->main->content + p->start, (p->i - p->start) + 1);
			if (tmp == NULL)
				(err_msg("malloc", ERR_MALLOC, 0), clean_exit_shell(FAILURE));
			(void)yama(ADD, tmp, 0);
			p->seg_elems[p->token_count++] = tmp;
		}
		else
		{
			tmp = ft_strldup(p->main->content + p->start, (p->i - p->start));
			if (tmp == NULL)
				(err_msg("malloc", ERR_MALLOC, 0), clean_exit_shell(FAILURE));
			(void)yama(ADD, tmp, 0);
			p->seg_elems[p->token_count++] = tmp;
		}
	}
}

static void	__init(t_token_parser *p)
{
	p->closed_quotes[0] = true;
	p->closed_quotes[1] = true;
	p->i = 0;
	p->start = p->i;
	p->was_closed = true;
}

static void	__get_closed_quotes(t_token_parser *p)
{
	if (p->main->content[p->i] == '\'')
		p->closed_quotes[0] = switch_bool(p->closed_quotes[0]);
	else if (p->main->content[p->i] == '"')
		p->closed_quotes[1] = switch_bool(p->closed_quotes[1]);
	if (p->closed_quotes[0] == true && p->closed_quotes[1] == true)
		p->is_closed = true;
	else
		p->is_closed = false;
}

static void __parse_quoted_segment(t_token_parser *p)
{
	__init(p);
	while (p->main->content[p->i] != '\0')
	{
		__get_closed_quotes(p);
		if (p->is_closed == true && p->was_closed == false)
		{
			__take_seg_elem(p);
			p->i++;
			p->start = p->i;
		}
		else if (p->is_closed == true && p->main->content[p->i] == ' ')
		{
			__take_seg_elem(p);
			while (p->main->content[p->i] == ' ')
				p->i++;
			p->start = p->i;
		}
		else
			p->i++;
		p->was_closed = p->is_closed; // permet de garder une trace de l'etat precedent des guillemets
		if (p->main->content[p->i] == '\0' && (p->i > p->start))
			__take_seg_elem(p);
	}
}

char	**get_quoted_seg_elems(t_main_lst *main, t_token_parser *p)
{
	ft_bzero(p, sizeof(p));
	p->main = main;
	p->seg_elems = yama(CREATE_TAB, NULL,
	(sizeof(char *) * (ft_strlen(main->content) + 1)));
	if (p->seg_elems == NULL)
		(err_msg("malloc", ERR_MALLOC, 0), clean_exit_shell(FAILURE));
	while (p->main->content[p->i] != '\0')
		__parse_quoted_segment(p);
	p->seg_elems[p->token_count] = NULL;
	return (p->seg_elems);
}
