/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: annabrag <annabrag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/25 18:23:16 by pmateo            #+#    #+#             */
/*   Updated: 2024/10/23 20:07:54 by annabrag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing_lexing.h"

bool	switch_bool(bool closed)
{
	if (closed == true)
		closed = false;
	else
		closed = true;
	return (closed);
}

int	find_closing_quote(char *str, char quote)
{
	int	i;

	i = 1;
	while (str[i] != quote && str[i])
		i++;
	return (i);
}

bool	unclosed_quotes_return(bool closed[])
{
	if (closed[1] == false || closed[0] == false)
		return (true);
	else
		return (false);
}

char	*del_empty_quotes(char *str, int quote_idx)
{
	int		i;
	int		j;
	char	*new_str;

	i = 0;
	j = 0;
	new_str = yama(CREATE, NULL, (sizeof(char) * (ft_strlen(str) - 1)));
	secure_malloc(new_str, true);
	while (i != quote_idx)
	{
		new_str[i] = str[i];
		i++;
	}
	j = i + 2;
	while (str[j] != '\0')
	{
		new_str[i] = str[j];
		i++;
		j++;
	}
	new_str[i] = '\0';
	free_and_set_null(str);
	return (new_str);
}

char	*del_quote_pair(char *str, int first, int second)
{
	int		i;
	int		j;
	char	*new_str;

	i = 0;
	new_str = yama(CREATE, NULL, (sizeof(char) * (ft_strlen(str) - 1)));
	secure_malloc(new_str, true);
	while (i != first)
	{
		new_str[i] = str[i];
		i++;
	}
	j = i + 1;
	while (j != second)
		new_str[i++] = str[j++];
	j += 1;
	while (str[j] != '\0')
		new_str[i++] = str[j++];
	new_str[i] = '\0';
	free_and_set_null(str);
	return (new_str);
}
