/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: art3mis <art3mis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 20:42:03 by pmateo            #+#    #+#             */
/*   Updated: 2024/09/03 23:54:31 by art3mis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
	Handle $? which should *expand* to the exit status
	of the most recently executed foreground pipeline
*/

static char	*__del_var(char *str, char *var, size_t var_size)
{
	char	*new_str;
	char	*end_var;

	end_var = var + var_size;
	new_str = malloc((ft_strlen(str) - var_size) * sizeof(char));
	if (new_str == NULL)
		return (NULL);
	ft_strlcpy(new_str, str, (var - str));
	ft_strcpy(new_str + ((var - 1) - str), end_var);
	free(str);
	return (new_str);
}

// EXEMPLE : gg"$USER"wp = gg"pmateo"wp 
static char	*__add_var_value(char *str, char *var, char *var_value, size_t vv_size)
{
	char	*new_str;
	char	*start_str;
	size_t	i;
	size_t	len_var;

	start_str = str;
	len_var = 0;
	while ((var[len_var] >= 'A' && var[len_var] <= 'Z') 
			|| (var[len_var] >= 'a' && var[len_var] <= 'z')
			|| (var[len_var] >= '0' && var[len_var] <= '9')
			|| var[len_var] == '_')
		len_var++;
	new_str = malloc(ft_strlen(str) + (vv_size - len_var) * (sizeof(char)));
	if (new_str == NULL)
		return (NULL);
	i = 0;
	while (str != (var - 1))
		new_str[i++] = *str++;
	while (*var_value)
		new_str[i++] = *var_value++;
	str += len_var + 1;
	while (*str)
		new_str[i++] = *str++;
	new_str[i] = '\0';
	return (free(start_str), new_str);
}

static char	*__handle_expand(char *str, char *var, char **envp)
{
	char	*to_find;
	char	*var_value;

	to_find = take_var(str, var);
	// printf("to_find = %s\n", to_find);
	var_value = search_var(to_find, envp);
	// printf("var_value = %s\n", var_value);
	if (var_value == NULL)
		str = __del_var(str, var, ft_strlen(to_find));
	else
		str = __add_var_value(str, var, var_value, ft_strlen(var_value));
	return (str);
}

//EXEMPLE : "'$USER'" = "'pmateo'" | '"$USER"' = '"$USER"'
char	*expand(char *str, char **envp)
{
	int		i;
	bool 	closed[2];

	i = 0;
	closed[0] = true;
	closed[1] = true;
	while (str[i] != '\0')
	{
		if (str[i] == '"' && closed[1] != false)
			closed[0] = switch_bool(closed[0]);
		else if (str[i] == '\'' && closed[0] != false)
			closed[1] = switch_bool(closed[1]);
		if ((str[i] == '$' && closed[1] != false) 
			&& (str[i + 1] != ' ' && str[i + 1] != '"' 
			&& str[i + 1] != '\'' && str[i + 1] != '$')) 
		{
			str = __handle_expand(str, &str[i + 1], envp);
			if (str == NULL)
				return (NULL);
		}
		i++;
	}
	str = empty_quotes(str);
	return (str);
}
