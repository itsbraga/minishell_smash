/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_before_main.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: art3mis <art3mis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 19:35:48 by art3mis           #+#    #+#             */
/*   Updated: 2024/09/17 17:03:02 by art3mis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	__first_check(t_parser *p)
{
	while (ft_isspace(p->user_input[p->i]) == 1)
		p->i++;
	if (p->user_input[p->i] == '\0')
		return (FAILURE);
	return (SUCCESS);
}

static int	__quote_parser(t_parser *p)
{
	char    *tmp;

	if (__first_check(p) == FAILURE)
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
	(void)yama(ADD, tmp, 0);
	p->segment[p->seg_count] = tmp;
	p->seg_count++;
	if (p->user_input[p->i] == '|')
		p->i++;
	return (SUCCESS);
}

// static int	__pipe_check(t_parser *p)
// {
// 	if (p->user_input[p->i] == '|')
// 	{
// 		p->i++;
// 		while (ft_isspace(p->user_input[p->i]) == 1)
// 			p->i++;
// 		if (p->user_input[p->i] == '\0')
// 			return (FAILURE);
// 	}
// 	return (SUCCESS);
// }

char	**split_user_input(char *input)
{
	t_parser	p;
	size_t		len_input;

	if (unclosed_quotes(input) == true)
		return (err_msg(NULL, "unclosed quotes, please try again", 0), NULL);
	ft_bzero(&p, sizeof(p));
	p.user_input = input;
	len_input = ft_strlen(p.user_input);
	if (p.user_input == NULL || p.user_input[0] == '\0')
		return (NULL);
	if (ft_strchr(input, '\'') != NULL || ft_strchr(input, '"') != NULL)
	{
		p.segment = yama(CREATE, NULL, (sizeof(char *) * (len_input + 1)));
		if (p.segment == NULL)
			return (err_msg("malloc", ERR_MALLOC, 0), NULL);
		while (p.user_input[p.i] != '\0')
		{
			if (__quote_parser(&p) == FAILURE)
				return (NULL);
		}
		p.segment[p.seg_count] = NULL;
	}
	else
	{
		p.segment = ft_split(input, '|');
		(void)yama(ADD, p.segment, 0);
	}
	return (p.segment);
}
