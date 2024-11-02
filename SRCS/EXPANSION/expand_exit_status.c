/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_exit_status.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: art3mis <art3mis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 00:07:17 by pmateo            #+#    #+#             */
/*   Updated: 2024/11/02 03:04:40 by art3mis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser_lexer.h"

static char	*__add_exit_status_value(char *str, char *var, char *var_value,
size_t vv_size)
{
	char	*new_str;
	char	*start_str;
	int		i;

	start_str = str;
	new_str = malloc(sizeof(char) * (ft_strlen(str) + (vv_size - 1)));
	secure_malloc(new_str, true);
	i = 0;
	while (str != (var - 1))
		new_str[i++] = *str++;
	while (*var_value)
		new_str[i++] = *var_value++;
	str += 2;
	while (*str)
		new_str[i++] = *str++;
	new_str[i] = '\0';
	free_and_set_null((void **)&start_str);
	return (new_str);
}

char	*handle_last_exit_status(char *str, char *var)
{
	char	*var_value;

	var_value = ft_itoa(ft_exit_status(0, GET));
	secure_malloc(var_value, true);
	str = __add_exit_status_value(str, var, var_value, ft_strlen(var_value));
	free_and_set_null((void **)&var_value);
	return (str);
}
