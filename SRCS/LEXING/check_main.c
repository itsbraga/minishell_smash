/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: art3mis <art3mis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 22:56:00 by art3mis           #+#    #+#             */
/*   Updated: 2024/10/21 00:11:27 by art3mis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	__init_token_parser(t_token_parser *p)
{
	p->closed_quotes[0] = true;
	p->closed_quotes[1] = true;
	p->i = 0;
	p->start = p->i;
}

static void	__get_closed_quotes(t_token_parser *p)
{
	if (p->main_content[p->i] == '\'')
		p->closed_quotes[0] = switch_bool(p->closed_quotes[0]);
	else if (p->main_content[p->i] == '"')
		p->closed_quotes[1] = switch_bool(p->closed_quotes[1]);
}

static void	__take_seg_elem(t_token_parser *p)
{
	char	*tmp;

	tmp = NULL;
	if (p->i > p->start)
	{
		tmp = ft_strldup(p->main_content + p->start, (p->i - p->start));
		secure_malloc(tmp, true);
		// (void)yama(ADD, tmp, 0);
		p->seg_elems[p->token_count] = tmp;
		p->token_count++;
	}
	p->start = p->i; // Redéfinir le début pour le prochain token
}

static void	__redir_case(t_token_parser *p)
{
	__take_seg_elem(p);
	if (p->main_content[p->i] == p->main_content[p->i + 1])
		p->i += 2;
	else
		p->i++;
	__take_seg_elem(p);
}

void	parse_segment(t_token_parser *p)
{
	__init_token_parser(p);
	while (p->main_content[p->i] != '\0')
	{
		__get_closed_quotes(p);
		if (is_redir(&(p->main_content[p->i])) == true
			&& p->closed_quotes[0] == true && p->closed_quotes[1] == true)
			__redir_case(p);
		else if (p->main_content[p->i] == ' '
			&& p->closed_quotes[0] == true && p->closed_quotes[1] == true)
		{
			__take_seg_elem(p);
			while (ft_isspace(p->main_content[p->i]) == 1)
				p->i++;
			p->start = p->i;
		}
		else
			p->i++;
		if (p->main_content[p->i] == '\0' && (p->i > p->start))
			__take_seg_elem(p);
	}
}
