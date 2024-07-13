/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmateo <pmateo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 20:42:03 by pmateo            #+#    #+#             */
/*   Updated: 2024/07/12 20:59:00 by pmateo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../INCLUDES/mini_parsing.h"

void	remove_var()
{
	
}

void	add_var_value()
{
	
}

char	*expand(char *str, char *var, char **envp)
{
	int		i;
	int		j;
	char 	*to_find;
	char	*var_value;

	i = 0;
	to_find = take_var(str, var);
	var_value = search_var(to_find, envp);
	if (var_value == NULL)
		remove_var();
	else
		add_var_value();
	//
	
}

void	handle_expand(char *str, char **envp)
{
	int		i;
	bool 	closed;
	char	quote;

	i = 0;
	closed = true;
	quote = NULL;
	while (str[i])
	{
		if (str[i] == '\'' && quote != '"')
		{
			quote = '\'';
			closed = switch_bool(closed);
		}
		if (str[i] == '"' && quote != '\'')
		{
			quote = '"';
			closed = switch_bool(closed);
		}
		if (str[i] == '$' && (quote != '\'' && closed != false))
			str = expand(str, &str[i], envp);
		i++;
	}
}