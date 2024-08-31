/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmateo <pmateo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 20:42:03 by pmateo            #+#    #+#             */
/*   Updated: 2024/08/31 17:50:04 by pmateo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../INCLUDES/mini_parsing.h"

static char	*__del_var(char *str, char *var, size_t var_size)
{
	char	*new_str;
	char	*end_var;

	end_var = var + var_size;
	new_str = malloc((ft_strlen(str) - var_size) * sizeof(char));
	if (!new_str)
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
	size_t	var_len;

	start_str = str;
	var_len = 0;
	while ((var[var_len] >= 'A' && var[var_len] <= 'Z')
			|| (var[var_len] >= '0' && var[var_len] <= '9')
			|| var[var_len] == '_')
		var_len++;
	new_str = malloc(ft_strlen(str) + (vv_size - var_len) * (sizeof(char)));
	if (new_str == NULL)
		return (NULL);
	i = 0;
	while (str != (var - 1))
		new_str[i++] = *str++;
	while (*var_value)
		new_str[i++] = *var_value++;
	str += var_len + 1;
	while (*str)
		new_str[i++] = *str++;
	new_str[i] = '\0';
	free(start_str);
	return (new_str);
}

static char	*__handle_expand(char *str, char *var, char **envp)
{
	char 	*to_find;
	char	*var_value;
	to_find = take_var(str, var);
	printf("to_find = %s\n", to_find);
	var_value = search_var(to_find, envp);
	printf("var_value = %s\n", var_value);
	if (var_value == NULL)
		str = __del_var(str, var, ft_strlen(to_find));
	else
		str = __add_var_value(str, var, var_value, ft_strlen(var_value));
	return (str);
}

//EXEMPLE : "'$USER'" = "'pmateo'" | '"$USER"' = '"$USER"'
char *expand(char *str, char **envp)
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
		if (str[i] == '$' && closed[1] != false && str[i + 1])
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
