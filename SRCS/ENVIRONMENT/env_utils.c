/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: annabrag <annabrag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 14:15:10 by pmateo            #+#    #+#             */
/*   Updated: 2024/11/04 19:22:17 by annabrag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	update_shlvl_export(t_env_lst **exp_env)
{
	t_env_lst	*curr;
	int			var_value;
	char		*new_value;
	char		*tmp;

	curr = *exp_env;
	while (curr != NULL)
	{
		if (ft_strncmp(curr->content, "SHLVL=", 6) == 0)
		{
			var_value = ft_atoi(curr->content + 7, 0);
			var_value += 1;
			new_value = ft_itoa(var_value);
			secure_malloc(new_value, true);
			(void)yama(ADD, new_value, 0);
			free(curr->content);
			curr->content = ft_strjoin("SHLVL=", new_value);
			secure_malloc(curr->content, true);
			tmp = curr->content;
			curr->content = add_quotes_to_value(curr->content);
			free_and_set_null((void **)&tmp);
			(void)yama(REMOVE, new_value, 0);
		}
		curr = curr->next;
	}
}

void	update_shlvl(t_env_lst **env)
{
	t_env_lst	*curr;
	int			var_value;
	char		*new_value;

	curr = *env;
	while (curr != NULL)
	{
		if (ft_strncmp(curr->content, "SHLVL=", 6) == 0)
		{
			var_value = ft_atoi(curr->content + 6, 0);
			var_value += 1;
			new_value = ft_itoa(var_value);
			secure_malloc(new_value, true);
			(void)yama(ADD, new_value, 0);
			free(curr->content);
			curr->content = ft_strjoin("SHLVL=", new_value);
			secure_malloc(curr->content, true);
			(void)yama(REMOVE, new_value, 0);
		}
		curr = curr->next;
	}
}

static size_t	__get_env_lst_size(t_env_lst **env)
{
	size_t		size;
	t_env_lst	*curr;

	size = 0;
	curr = *env;
	while (curr != NULL)
	{
		size++;
		curr = curr->next;
	}
	return (size);
}

size_t	get_env_tab_size(char **env)
{
	size_t	size;

	size = 0;
	while (env[size] != NULL)
		size++;
	return (size);
}

char	**recreate_env_tab(t_env_lst **env)
{
	char		**tab;
	size_t		size;
	t_env_lst	*curr;
	int			i;

	size = (sizeof(char *) * (__get_env_lst_size(env) + 1));
	tab = yama(CREATE_TAB, NULL, size);
	secure_malloc(tab, true);
	curr = *env;
	i = 0;
	while (curr != NULL)
	{
		tab[i] = ft_strdup(curr->content);
		secure_malloc(tab[i], true);
		(void)yama(ADD, tab[i], 0);
		i++;
		curr = curr->next;
	}
	tab[i] = NULL;
	return (tab);
}
