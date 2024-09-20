/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_quotes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: annabrag <annabrag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 22:56:00 by art3mis           #+#    #+#             */
/*   Updated: 2024/09/20 17:44:24 by annabrag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	__count_tokens(t_main_lst *main, t_token_parser *p)
{
	int		token_count;

	ft_bzero(p, sizeof(p));
	p->main = main;
	p->closed_quotes[0] = true;
	p->closed_quotes[1] = true;
	token_count = 0;
	while (p->main->content[p->i] != '\0')
	{
		if (token_count == 0)
			token_count++;
		if (p->main->content[p->i] == '\'')
			p->closed_quotes[0] = switch_bool(p->closed_quotes[0]);
		else if (p->main->content[p->i] == '"')
			p->closed_quotes[1] = switch_bool(p->closed_quotes[1]);
		if ((p->main->content[p->i] == ' ' || p->main->content[p->i] == '\0')
			&& p->closed_quotes[0] == true && p->closed_quotes[1] == true)
			token_count++;
		p->i++;
	}
	return (token_count);
}

static int	__quote_parser_main_lst(t_token_parser *p)
{
    char    *tmp;

    p->closed_quotes[0] = true;
    p->closed_quotes[1] = true;
    p->i = 0;
    p->start = p->i;
    while (p->main->content[p->i] != '\0')
	{
		if (p->main->content[p->i] == '\'')
			p->closed_quotes[0] = switch_bool(p->closed_quotes[0]);
		else if (p->main->content[p->i] == '"')
			p->closed_quotes[1] = switch_bool(p->closed_quotes[1]);
		if (p->main->content[p->i] == ' ' && p->closed_quotes[0] == true
			&& p->closed_quotes[1] == true)
			break ;
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
	int	nb_tokens;

	ft_bzero(p, sizeof(p));
	p->main = main;
	nb_tokens = __count_tokens(p->main, p);
	p->seg_elems = yama(CREATE, NULL, (sizeof(char *) * (nb_tokens + 1)));
	if (p->seg_elems == NULL)
		(err_msg("malloc", ERR_MALLOC, 0), clean_exit_shell(FAILURE));
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

char	**split_main_content2(t_main_lst *main)
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
