/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: art3mis <art3mis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 19:35:48 by art3mis           #+#    #+#             */
/*   Updated: 2024/09/05 22:25:20 by art3mis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_input(t_parser *p)
{
	if (handle_quotes_modif(p->user_input) == NULL)
		return (errmsg_exit(2, FAILURE));
	while (ft_isspace(p->user_input[p->i]) == 1)
			p->i++;
	if (p->user_input[p->i] == '\0')
		return (FAILURE);
	else if (p->user_input[p->i] == '|')
	{
		// printf("ici\n");
		// p->i++;
		// while (ft_isspace(p->user_input[p->i]) == 1)
		// 	p->i++;
		// printf("tobby\n");
		// if (p->user_input[p->i] == '\0')
			return (errmsg_exit(1, FAILURE));
	}
	return (SUCCESS);
}

int	parser(t_parser *p)
{
	char    *tmp;
	
	if (check_input(p) == FAILURE)
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
	p->tokens[p->token_count] = tmp;
	p->token_count++;
	if (p->user_input[p->i] == '|')
		p->i++;
	return (SUCCESS);
}

char	**split_user_input(char *input)
{
	t_parser	p;

	ft_bzero(&p, sizeof(p));
	p.user_input = input;
	if (p.user_input == NULL || p.user_input[0] == '\0')
		return (NULL);
	if (ft_strchr(input, '"') != NULL || ft_strchr(input, '\'') != NULL)
	{
		p.tokens = malloc(sizeof(char *) * (ft_strlen(p.user_input) + 1));
		if (p.tokens == NULL)
			return (NULL);
		while (p.user_input[p.i] != '\0')
		{
			if (parser(&p) == FAILURE)
				return (NULL);
		}
		p.tokens[p.token_count] = NULL;
	}
	else
		p.tokens = ft_split(input, '|');
	return (p.tokens);
}
