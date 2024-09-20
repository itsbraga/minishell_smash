/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_before_token.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: annabrag <annabrag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 22:56:00 by art3mis           #+#    #+#             */
/*   Updated: 2024/09/20 17:24:03 by annabrag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	__quote_parser_main_lst(t_token_parser *p)
{
    char    *tmp;

    p->closed_quotes[0] = true;
    p->closed_quotes[1] = true;
	p->i = 0;
    p->start = p->i;
	printf("main->content: *%s*\n", p->main->content);
    while (p->main->content[p->i] != '\0')
	{
		if (p->main->content[p->i] == '\'')
			p->closed_quotes[0] = switch_bool(p->closed_quotes[0]);
		else if (p->main->content[p->i] == '"')
			p->closed_quotes[1] = switch_bool(p->closed_quotes[1]);
		if (p->main->content[p->i] == ' ' && p->closed_quotes[0] == true && p->closed_quotes[1] == true)
		{
			tmp = ft_strldup(p->main->content + p->start, p->i - p->start);
			if (tmp == NULL)
				(err_msg("malloc", ERR_MALLOC, 0), clean_exit_shell(FAILURE));
			(void)yama(ADD, tmp, 0);
			p->seg_elems[p->token_count++] = tmp;
			p->start = p->i + 1;
		}
		p->i++;
	}
	if (p->i > p->start)
	{
		tmp = ft_strldup(p->main->content + p->start, p->i - p->start);
		if (tmp == NULL)
			(err_msg("malloc", ERR_MALLOC, 0), clean_exit_shell(FAILURE));
		(void)yama(ADD, tmp, 0);
		p->seg_elems[p->token_count++] = tmp;
	}
	// if (p->main->content[p->i] == ' ')
	// 	p->i++;
}

static char	**__split_quoted_tokens(t_main_lst *main, t_token_parser *p)
{
	ft_bzero(p, sizeof(p));
	p->main = main;
	p->seg_elems = yama(CREATE_TAB, NULL, (sizeof(char *) * (ft_strlen(main->content) + 1)));
	if (p->seg_elems == NULL)
		(err_msg("malloc", ERR_MALLOC, 0), clean_exit_shell(FAILURE));
	while (p->main != NULL)
	{
		while (p->main->content[p->i] != '\0')
			__quote_parser_main_lst(p);
		p->main = p->main->next;
		p->i = 0;
	}
	p->seg_elems[p->token_count] = NULL;
	return (p->seg_elems);
}

char	**split_main_content(t_main_lst *main)
{
	t_token_parser	p;

	ft_bzero(&p, sizeof(p));
	p.main = main;
	if (p.main == NULL || p.main->content == NULL)
		return (NULL);
	if (ft_strchr(p.main->content, '\'') != NULL || ft_strchr(p.main->content, '"') != NULL)
	{
		p.seg_elems = __split_quoted_tokens(p.main, &p);
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
