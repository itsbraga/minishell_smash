/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: annabrag <annabrag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 20:42:22 by pmateo            #+#    #+#             */
/*   Updated: 2024/10/31 06:26:41 by annabrag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser_lexer.h"

bool	unclosed_quotes(char *str)
{
	int		i;
	bool	closed[2];

	i = 0;
	closed[0] = true;
	closed[1] = true;
	while (str[i] != '\0')
	{
		if (str[i] == '\'')
		{
			if (closed[0] == true && closed[1] == true)
				closed[0] = false;
			else
				closed[0] = true;
		}
		else if (str[i] == '"')
		{
			if (closed[1] == true && closed[0] == true)
				closed[1] = false;
			else
				closed[1] = true;
		}
		i++;
	}
	return (unclosed_quotes_return(closed));
}

static bool	__handle_empty_quotes(char *str, int i, bool closed_quotes[])
{
	if ((str[i] == '"' && str[i + 1] == '"')
		&& (closed_quotes[1] == true && closed_quotes[0] == true))
		return (true);
	else if ((str[i] == '\'' && str[i + 1] == '\'')
		&& (closed_quotes[1] == true && closed_quotes[0] == true))
		return (true);
	get_closed_quotes(str[i], closed_quotes);
	return (false);
}

char	*empty_quotes(char *str)
{
	int		i;
	bool	closed_quotes[2];

	i = 0;
	closed_quotes[0] = true;
	closed_quotes[1] = true;
	while (str[i] != '\0')
	{
		if (__handle_empty_quotes(str, i, closed_quotes) == true)
		{
			str = del_empty_quotes(str, i);
			i = -1;
			closed_quotes[0] = true;
			closed_quotes[1] = true;
		}
		i++;
	}
	return (str);
}

char	*other_quotes(char *str)
{
	int		i;
	int		closing_quote;

	i = 0;
	closing_quote = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '"')
		{
			closing_quote = find_closing_quote(&(str[i]), '"');
			str = del_quote_pair(str, i, (i + closing_quote));
			i += (closing_quote - 1);
		}
		else if (str[i] == '\'')
		{
			closing_quote = find_closing_quote(&(str[i]), '\'');
			str = del_quote_pair(str, i, (i + closing_quote));
			i += (closing_quote - 1);
		}
		else
			i++;
	}
	return (str);
}