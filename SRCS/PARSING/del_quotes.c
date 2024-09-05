/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   del_quotes.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: art3mis <art3mis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/25 18:23:16 by pmateo            #+#    #+#             */
/*   Updated: 2024/09/05 19:19:59 by art3mis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*del_empty_quotes(char *str, int quote_idx)
{
	int	i;
	int	j;
	char *new_str;

	i = 0;
	j = 0;
	new_str = malloc(sizeof(char) * (ft_strlen(str) - 1));
	if (new_str == NULL)
		return (NULL);
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
	free(str);
	return (new_str);
}

char	*del_quote_pair(char *str, int first, int second)
{
	int 	i;
	int		j;
	char	*new_str;

	i = 0;
	new_str = malloc(sizeof(char) * (ft_strlen(str) - 1));
	if (new_str == NULL)
		return (NULL);
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
	free(str);
	return (new_str);
}
