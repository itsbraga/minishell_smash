/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: annabrag <annabrag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 20:56:57 by pmateo            #+#    #+#             */
/*   Updated: 2024/09/20 15:43:26 by annabrag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	if (value == NULL)
		(err_msg("malloc", ERR_MALLOC, 0), clean_exit_shell(FAILURE));
	(void)yama(ADD, value, 0);
	return (value);
}

// LA VARIABLE CORRESPOND A TOUT CARACTERE ALPHANUMERIQUE QUI VIENT APRES LE $
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
	to_find = ft_strldup(&str[i], (j - i));
	if (to_find == NULL)
		(err_msg("malloc", ERR_MALLOC, 0), clean_exit_shell(FAILURE));
	(void)yama(ADD, to_find, 0);
	return (to_find);
}

char 	*search_var(char *to_find, t_env_lst *env)
{
	char		*to_cmp;
	t_env_lst	*node;

	to_cmp = NULL;
	node = env;
	while (node != NULL)
	{
		to_cmp = ft_strldup(node->content, len_to_equal(node->content));
		if (to_cmp == NULL)
			(err_msg("malloc", ERR_MALLOC, 0), clean_exit_shell(FAILURE));
		(void)yama(ADD, to_cmp, 0);
		if (ft_strcmp(to_find, to_cmp) == 0)
		{
			free(to_cmp);
			return (__take_var_value(node->content));
		}
		else
		{
			free(to_cmp);
			to_cmp = NULL;
			node = node->next;
		}
	}
	return (NULL);
}
