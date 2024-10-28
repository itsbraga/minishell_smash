/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_exit_code.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmateo <pmateo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 00:07:17 by pmateo            #+#    #+#             */
/*   Updated: 2024/10/28 01:38:27 by pmateo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

 # include "parsing_lexing.h"

 char	*add_exit_code_value(char *str, char *var, char *var_value,
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
	return (free_and_set_null(start_str), new_str);
}

char	*handle_last_exit_code(char *str, char *var)
{
	char	*var_value;

	var_value = ft_itoa(ft_exit_status(0, GET));
	secure_malloc(var_value, true);
	str = add_exit_code_value(str, var, var_value, ft_strlen(var_value));
	free_and_set_null(var_value);
	return (str);
}
