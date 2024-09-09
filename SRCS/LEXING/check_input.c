/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: art3mis <art3mis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 19:35:48 by art3mis           #+#    #+#             */
/*   Updated: 2024/09/10 01:17:24 by art3mis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_input_before_quotes(t_parser *p)
{
	while (ft_isspace(p->user_input[p->i]) == 1)
			p->i++;
	if (p->user_input[p->i] == '\0')
		return (FAILURE);
	else if (p->user_input[p->i] == '|')
	{
		printf("ici\n");
		p->i++;
		while (ft_isspace(p->user_input[p->i]) == 1)
			p->i++;
		printf("tobby\n");
		if (p->user_input[p->i] == '\0')
		{
			err_msg(NULL, ERR_NEAR_PIPE, 0);
			return (FAILURE);
		}
	}
	return (SUCCESS);
}

int	quote_parser(t_parser *p)
{
	char    *tmp;
	
	if (check_input_before_quotes(p) == FAILURE)
		return (FAILURE);
	p->closed_quotes[0] = true;
	p->closed_quotes[1] = true;
	p->start = p->i;
	while (p->user_input[p->i] != '\0' && (p->user_input[p->i] != '|'
			|| p->closed_quotes[0] == false || p->closed_quotes[1] == false))
	{
		if (p->user_input[p->i] == '\'')
			p->closed_quotes[0] = switch_bool(p->closed_quotes[0]);
		else if (p->user_input[p->i] == '"')
			p->closed_quotes[1] = switch_bool(p->closed_quotes[1]);
		p->i++;
	}
	tmp = ft_strldup(p->user_input + p->start, p->i - p->start);
	if (tmp == NULL)
		return (FAILURE);
	p->elems[p->token_count] = tmp;
	p->token_count++;
	if (p->user_input[p->i] == '|')
		p->i++;
	return (SUCCESS);
}

char	**split_user_input(char *input)
{
	t_parser	p;

	if (unclosed_quotes(input) == true)
		return (err_msg(NULL, "unclosed quotes, please try again", 0), NULL);
	ft_bzero(&p, sizeof(p));
	p.user_input = input;
	if (p.user_input == NULL || p.user_input[0] == '\0')
		return (NULL);
	if (ft_strchr(input, '"') != NULL || ft_strchr(input, '\'') != NULL)
	{
		p.elems = malloc(sizeof(char *) * (ft_strlen(p.user_input) + 1));
		if (p.elems == NULL)
			return (NULL);
		while (p.user_input[p.i] != '\0')
		{
			if (quote_parser(&p) == FAILURE)
				return (NULL);
		}
		p.elems[p.token_count] = NULL;
	}
	else
		p.elems = ft_split(input, '|');
	return (p.elems);
}
