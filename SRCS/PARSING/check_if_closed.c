/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_if_closed.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: annabrag <annabrag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 16:44:18 by annabrag          #+#    #+#             */
/*   Updated: 2024/08/16 15:50:03 by annabrag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
		printf("%s%s\n", "minishell: ", strerror(errno));
		return (false);
	}
}

bool	is_closed_dbquote(char **str)
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
		printf("%s%s\n", "minishell: ", strerror(errno));
		return (false);
	}
}
