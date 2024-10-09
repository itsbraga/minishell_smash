/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: annabrag <annabrag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 19:35:48 by art3mis           #+#    #+#             */
/*   Updated: 2024/10/09 21:29:54 by annabrag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	__front_check(t_parser *p)
{
	while (ft_isspace(p->user_input[p->i]) == 1)
		p->i++;
	if (p->user_input[p->i] == '\0')
		return (FAILURE);
	return (SUCCESS);
}

static void	__init_parser(t_parser *p)
{
	p->closed_quotes[0] = true;
	p->closed_quotes[1] = true;
	p->start = p->i;
}

static void	__pipe_check(t_parser *p)
{
	if (p->user_input[p->i] == '|')
	{
		p->i++;
		if (p->user_input[p->i] == '|')
		{
			err_msg(NULL, "||", 2);
			exit(FAILURE);
		}
		while (p->user_input[p->i] != '\0'
			&& ft_isspace(p->user_input[p->i]) == 1)
			p->i++;
		if (p->user_input[p->i] == '|' || p->user_input[p->i] == '\0')
		{
			err_msg(NULL, "|", 2);
			exit(FAILURE); // verifier s'il faut quitter ou pas ici
		}
	}
}

void	parse_input(t_parser *p)
{
	char	*tmp;

	if (__front_check(p) == FAILURE)
		exit(FAILURE);
	__init_parser(p);
	while (p->user_input[p->i] != '\0')
	{
		if (p->user_input[p->i] == '\'')
			p->closed_quotes[0] = switch_bool(p->closed_quotes[0]);
		else if (p->user_input[p->i] == '"')
			p->closed_quotes[1] = switch_bool(p->closed_quotes[1]);
		else if (p->user_input[p->i] == '|' && p->closed_quotes[0] == true
			&& p->closed_quotes[1] == true)
			break ;
		p->i++;
	}
	tmp = ft_strldup(p->user_input + p->start, (p->i - p->start));
	secure_malloc(tmp);
	(void)yama(ADD, tmp, 0);
	p->segment[p->seg_count] = tmp;
	p->seg_count++;
	if (p->closed_quotes[0] == true && p->closed_quotes[1] == true)
		__pipe_check(p);
}
