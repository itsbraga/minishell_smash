/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: art3mis <art3mis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 20:42:03 by pmateo            #+#    #+#             */
/*   Updated: 2024/10/03 23:25:33 by art3mis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*__del_var(char *str, char *var, size_t var_size)
{
	char	*new_str;
	char	*end_var;

	end_var = var + var_size;
	new_str = yama(CREATE, NULL, (sizeof(char) * (ft_strlen(str) - var_size)));
	secure_malloc(new_str);
	ft_strlcpy(new_str, str, (var - str));
	ft_strcpy(new_str + ((var - 1) - str), end_var);
	free(str);
	return (new_str);
}

static char	*__add_var_value(char *str, char *var, char *var_value, size_t vv_size)
{
	char	*new_str;
	char	*start_str;
	int		i;
	size_t	len_var;

	start_str = str;
	len_var = 0;
	while ((var[len_var] >= 'A' && var[len_var] <= 'Z')
			|| (var[len_var] >= 'a' && var[len_var] <= 'z')
			|| (var[len_var] >= '0' && var[len_var] <= '9')
			|| var[len_var] == '_')
		len_var++;
	new_str = yama(CREATE, NULL, (sizeof(char) * (ft_strlen(str) + (vv_size - len_var))));
	secure_malloc(new_str);
	i = 0;
	while (str != (var - 1))
		new_str[i++] = *str++;
	while (*var_value)
		new_str[i++] = *var_value++;
	str += len_var + 1;
	while (*str)
		new_str[i++] = *str++;
	new_str[i] = '\0';
	free(start_str);
	return (new_str);
}

static	char	*handle_last_exit_code (t_data *d, char *str, char *var)
{
	char	*var_value;

	var_value = NULL;
	var_value = ft_itoa(d->last_exit_status);
	secure_malloc(var_value);
	(void)yama(ADD, var_value, 0);
	str = __add_var_value(str, var, var_value, ft_strlen(var_value));
	return (str);
}

static	char	*__handle_expand(t_data *d, char *str, char *var)
{
	char	*to_find;
	char	*var_value;

	to_find = NULL;
	var_value = NULL;
	if (*var == '?')
		handle_last_exit_code(d, str, var);
	else if (*var == '"' || *var == '\'')
		str = __clean_translated_variable(str, var);
	else
	{
		to_find = take_var(str, var);
		var_value = search_var(to_find, d->env);
		if (var_value == NULL)
			str = __del_var(str, var, ft_strlen(to_find));
		else
			str = __add_var_value(str, var, var_value, ft_strlen(var_value));
	}
	if (to_find != NULL)
		free(to_find);
	if (var_value != NULL)
		free(var_value);
	return (str);
}

char	*expand(t_data *d, char *str, bool in_heredoc)
{
	int		i;
	bool 	closed_quotes[2];

	i = 0;
	closed_quotes[0] = true;
	closed_quotes[1] = true;
	while (str[i] != '\0')
	{
		if (str[i] == '\'' && closed_quotes[0] == true)
			closed_quotes[1] = switch_bool(closed_quotes[1]);
		else if (str[i] == '"' && closed_quotes[0] == true)
			closed_quotes[0] = switch_bool(closed_quotes[0]);
		if ((str[i] == '$' && closed_quotes[0] == true) 
			&& (str[i + 1] != ' ' && str[i + 1] != '$')) 
		{
			str = __handle_expand(d, str, &(str[i + 1]));
			if (str == NULL)
				return (NULL);
		}
		i++;
	}
	if (in_heredoc == false)
		str = empty_quotes(str);
	return (str);
}
