/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmateo <pmateo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 20:42:22 by pmateo            #+#    #+#             */
/*   Updated: 2024/08/25 21:00:04 by pmateo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../INCLUDES/mini_parsing.h"

static bool	__unclosed_quotes(char *str)
{
	int		i;
	bool	closed[2];
	
	i = 0;
	closed[0] = true, closed[1] = true;
	while(str[i] != '\0')
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
static bool	__handle_empty_quotes(char *str, int i, bool **closed)
{
	if ((str[i] == '"' && str[i + 1] == '"') 
		&& (*closed[1] != false && *closed[0] != false))
		return (true);
	else if ((str[i] == '\'' && str[i + 1] == '\'') 
		&& (*closed[1] != false && *closed[0] != false))
		return (true);
	if (str[i] == '"' && *closed[1] != false)
		*closed[0] = switch_bool(*closed[0]);
	else if (str[i] == '\'' && closed[0] != false)
		*closed[1] = switch_bool(*closed[1]);
	return (false);
}

char	*empty_quotes(char *str)
{
	int		i;
	bool	closed[2];

	i = 0;
	closed[0] = true;
	closed[1] = true;
	while (str[i] != '\0')
	{
		if (__handle_empty_quotes2(str, i, &closed))
		{
			str = del_empty_quote(str, i);
			i = -1;
			closed[0] = true;
			closed[1] = true;
		}
		i++;
	}
	return (str);
}

char	*others_quotes(char *str)
{
	int	i;
	int closing_quote;

	i = 0;
	closing_quote = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '"')
		{
			closing_quote = find_closing_quote(&str[i], '"');
			str = del_quote_pair(str, i, (i + closing_quote));
			i = (i + closing_quote) - 2;
		}
		else if (str[i] == '\'')
		{
			closing_quote = find_closing_quote(&str[i], '\'');
			str = del_quote_pair(str, i, (i + closing_quote));
			i  = (i + closing_quote) - 2;
		}
		i++;
	}
	return (str);
}

char	*handle_quotes_and_expand(char *input, char **envp)
{
	(void)envp;
	if (unclosed_quotes(input) == true)
	{
		ft_putendl_fd("Unclosed quote !", 2);
		ft_putendl_fd("Aborting...", 2);
		exit(EXIT_FAILURE);
	}
	input = empty_quotes(input);
	input = handle_expand(input, envp);
	input = other_quotes(input);
	return (input);
}
