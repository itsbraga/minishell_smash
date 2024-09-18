/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_before_token.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: annabrag <annabrag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 22:56:00 by art3mis           #+#    #+#             */
/*   Updated: 2024/09/18 17:44:02 by annabrag         ###   ########.fr       */
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
				return (err_msg("malloc", ERR_MALLOC, 0), FAILURE);
			p->seg_elems[p->token_count++] = tmp;
			p->start = p->i + 1;
		}
		p->i++;
	}
	tmp = ft_strldup(p->main->content + p->start, p->i - p->start);
	if (tmp == NULL)
		return (err_msg("malloc", ERR_MALLOC, 0), FAILURE);
	(void)yama(ADD, tmp, 0);
	p->seg_elems[p->token_count++] = tmp;
	if (p->main->content[p->i] == ' ')
		p->i++;
	return (SUCCESS);
}

static char	**__split_quoted_tokens(t_main_lst *main, t_token_parser *p)
{
	ft_bzero(p, sizeof(p));
	p->main = main;
	p->seg_elems = yama(CREATE, NULL, (sizeof(char *) * (ft_strlen(main->content) + 1)));
	if (p->seg_elems == NULL)
		return (err_msg("malloc", ERR_MALLOC, 0), NULL);
	while (p->main != NULL)
	{
		while (p->main->content[p->i] != '\0')
		{
			if (__quote_parser_main_lst(p) == FAILURE)
			{
				free_tab(p->seg_elems);
				return (NULL);
			}
		}
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
		{
			free_tab(p.seg_elems);
			return (NULL);
		}
		// ajouter yama(ADD...) ici ?
	}
	else
	{
		p.seg_elems = ft_split(p.main->content, ' ');
		if (p.seg_elems == NULL)
		{
			free_tab(p.seg_elems);
			return (err_msg("malloc", ERR_MALLOC, 0), NULL);
		}
		(void)yama(ADD, p.seg_elems, 0);
	}
	return (p.seg_elems);
}