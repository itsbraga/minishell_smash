/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmateo <pmateo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 20:56:57 by pmateo            #+#    #+#             */
/*   Updated: 2024/09/02 14:17:09 by pmateo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../INCLUDES/mini_parsing.h"

size_t	len_to_equal(char *str)
{
	size_t	i;

	i = 0;
	while (str[i] != '=' && str[i] != '\0')
		i++;
	return (i);
}

char	*take_var_value(char *str)
{
	int	i;
	char	*value;

	i = 0;
	value = NULL;
	while (str[i] != '=')
		i++;
	value = ft_strdup((str + i + 1));
	return (value);
}
// LA VARIABLE CORRESPOND A TOUT CARACTERE ALPHANUMERIQUE QUI VIENT APRES LE $
char *take_var(char *str, char *var)
{
	int	i;
	int	j;
	char *to_find;

	i = 0;
	while ((str + i) != var)
		i++;
	j = i;
	while (str[j] && ((str[j] >= 'A' && str[j] <= 'Z')
			|| (str[j] >= 'a' && str[j] <= 'z')
			|| (str[j] >= '0' && str[j] <= '9')
			|| str[j] == '_'))
		j++;
	to_find = ft_strldup(&str[i], (j - i));
	return (to_find);
}

char 	*search_var(char *to_find, char **envp)
{
	int	i;
	char	*to_cmp;

	i = 0;
	to_cmp = NULL;
	while (envp[i])
	{
		to_cmp = ft_strldup(envp[i], len_to_equal(envp[i]));
		if (strcmp(to_find, to_cmp) == 0)
		{
			free(to_cmp);
			return (take_var_value(envp[i]));
		}
		else
		{
			free(to_cmp);
			to_cmp = NULL;
			i++;
		}
	}
	return (NULL);
}