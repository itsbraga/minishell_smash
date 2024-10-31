/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: annabrag <annabrag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 22:56:00 by art3mis           #+#    #+#             */
/*   Updated: 2024/10/31 06:07:44 by annabrag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser_lexer.h"

static void	__init_token_parser(t_token_parser *p)
{
	p->closed_quotes[0] = true;
	p->closed_quotes[1] = true;
	p->i = 0;
	p->start = p->i;
}

// p->start = p->i	--> redefini le debut du token
static void	__take_seg_elem(t_token_parser *p)
{
	char	*tmp;

	tmp = NULL;
	if (p->i > p->start)
	{
		tmp = ft_strldup(p->main_content + p->start, (p->i - p->start));
		secure_malloc(tmp, true);
		(void)yama(ADD, tmp, 0);
		p->seg_elems[p->token_count] = tmp;
		p->token_count++;
	}
	p->start = p->i;
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
		get_closed_quotes(p->main_content[p->i], p->closed_quotes);
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
