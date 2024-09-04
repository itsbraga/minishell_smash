/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: art3mis <art3mis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/25 18:08:17 by pmateo            #+#    #+#             */
/*   Updated: 2024/09/04 00:09:57 by art3mis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	switch_bool(bool closed)
{
	if (closed == true)
		closed = false;
	else
		closed = true;
	return (closed);
}

int		find_closing_quote(char *str, char quote)
{
	int	i;

	i = 1;
	while (str[i] != quote && str[i])
		i++;
	return (i);
}

bool	unclosed_quotes_return(bool closed[])
{
	if (closed[0] == false || closed[1] == false)
		return (true);
	else
		return (false);
}
	