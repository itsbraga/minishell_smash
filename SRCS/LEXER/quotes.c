/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: annabrag <annabrag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 16:44:18 by annabrag          #+#    #+#             */
/*   Updated: 2024/06/28 18:00:13 by annabrag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../INCLUDES/minishell.h"

bool	is_closed_squote(char **str)
{
	int	i;
	
	i = 0;
	if (*str[0] == '\'')
		i++;
	while (*str[i] != '\0')
		i++;
	if (*str[i] == '\'')
			return (true);
	else
	{
		printf("%s\n", "minishell: syntax error ⮕ unclosed quote");
		return (false);
	}
}

bool	is_closed_dquote(char **str)
{
	int	i;
	
	i = 0;
	if (*str[0] == '"')
		i++;
	while (*str[i] != '\0' && *str[i] != '$')
		i++;
	if (*str[i] == '"')
		return (true);
	else
	{
		printf("%s\n", "minishell: syntax error ⮕ unclosed quote");
		return (false);
	}
}
