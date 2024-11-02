/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: art3mis <art3mis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 20:56:57 by pmateo            #+#    #+#             */
/*   Updated: 2024/11/02 03:04:52 by art3mis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser_lexer.h"

size_t	len_to_equal(char *str)
{
	size_t	i;

	i = 0;
	while (str[i] != '=' && str[i] != '\0')
		i++;
	return (i);
}

static char	*__take_var_value(char *str)
{
	char	*value;
	int		i;

	i = 0;
	value = NULL;
	while (str[i] != '=')
		i++;
	value = ft_strdup((str + i + 1));
	secure_malloc(value, true);
	return (value);
}

char	*clean_translated_variable(char *str, char *var)
{
	char	*new_str;
	int		i;

	new_str = malloc(sizeof(char) * (ft_strlen(str) - 2));
	secure_malloc(new_str, true);
	i = 0;
	while (str != (var - 1))
		new_str[i++] = *str++;
	str += 2;
	while (*str != *var)
		new_str[i++] = *str++;
	str += 1;
	while (*str)
		new_str[i++] = *str++;
	new_str[i] = '\0';
	free_and_set_null((void **)&str);
	return (new_str);
}

char	*take_var(char *str, char *var)
{
	char	*to_find;
	int		i;
	int		j;

	i = 0;
	while ((str + i) != var)
		i++;
	j = i;
	while (str[j] && ((str[j] >= 'A' && str[j] <= 'Z')
			|| (str[j] >= 'a' && str[j] <= 'z')
			|| (str[j] >= '0' && str[j] <= '9')
			|| str[j] == '_'))
		j++;
	to_find = ft_strldup(&(str[i]), (j - i));
	secure_malloc(to_find, true);
	return (to_find);
}

char	*search_var(char *to_find, t_env_lst *env)
{
	char		*to_cmp;
	t_env_lst	*curr;

	to_cmp = NULL;
	curr = env;
	while (curr != NULL)
	{
		to_cmp = ft_strldup(curr->content, len_to_equal(curr->content));
		secure_malloc(to_cmp, true);
		if (ft_strcmp(to_find, to_cmp) == 0)
		{
			free_and_set_null((void **)&to_cmp);
			return (__take_var_value(curr->content));
		}
		else
		{
			free_and_set_null((void **)&to_cmp);
			curr = curr->next;
		}
	}
	return (NULL);
}
