/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_main_lst.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: art3mis <art3mis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 22:56:00 by art3mis           #+#    #+#             */
/*   Updated: 2024/09/16 01:16:56 by art3mis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	__quote_parser_main_lst(t_token_parser *p)
{
    char    *tmp;

    p->closed_quotes[0] = true;
    p->closed_quotes[1] = true;
    p->i = 0;
    p->start = p->i;
    while (p->main->content[p->i] != '\0' && (p->main->content[p->i] != ' '
            || p->closed_quotes[0] == false || p->closed_quotes[1] == false))
	{
		if (p->main->content[p->i] == '\'')
			p->closed_quotes[0] = switch_bool(p->closed_quotes[0]);
		else if (p->main->content[p->i] == '"')
			p->closed_quotes[1] = switch_bool(p->closed_quotes[1]);
		p->i++;
	}
	tmp = ft_strldup(p->main->content + p->start, p->i - p->start);
	if (tmp == NULL)
		return (FAILURE);
	p->seg_elems[p->token_count] = tmp;
	p->token_count++;
	if (p->main->content[p->i] == ' ')
		p->i++;
	return (SUCCESS);
}

static int	__count_tokens(t_main_lst *main, t_token_parser *p)
{
	char	quote;
	int		token_count;

	ft_bzero(p, sizeof(p));
	p->main = main;
	token_count = 0;
	while (p->main != NULL)
	{
		while (p->main->content[p->i] != '\0')
		{
			if (p->main->content[p->i] == '\'' || p->main->content[p->i] == '"')
			{
				quote = p->main->content[p->i];
				p->i++;
				while (p->main->content[p->i] != quote && p->main->content[p->i] != '\0')
					p->i++;
			}
			if (p->main->content[p->i] == ' ' || p->main->content[p->i] == '\0')
				token_count++;
			p->i++;
		}
		p->i = 0;
		main = main->next;
	}
	return (token_count);
}

char	**split_main_content(t_main_lst *main)
{
	t_token_parser	p;
	int	nb_tokens;

	ft_bzero(&p, sizeof(p));
	p.main = main;
	if (p.main == NULL || p.main->content == NULL)
		return (NULL);
	if (ft_strchr(main->content, '\'') != NULL || ft_strchr(main->content, '"') != NULL)
	{
		nb_tokens = __count_tokens(main, &p);
		p.seg_elems = malloc(sizeof(char *) * (nb_tokens + 1));
		if (p.seg_elems == NULL)
			return (err_msg("malloc", ERR_MALLOC, 0), NULL);
		while (p.main != NULL)
		{
			while (p.main->content[p.i] != '\0')
			{
				if (__quote_parser_main_lst(&p) == FAILURE)
					return (free_tab(p.seg_elems), NULL);
			}
			p.main = p.main->next;
			p.i = 0;
		}
		p.seg_elems[p.token_count] = NULL;
	}
	else
		p.seg_elems = ft_split(p.main->content, ' ');
	return (p.seg_elems);
}
