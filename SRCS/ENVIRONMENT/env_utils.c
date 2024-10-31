/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: annabrag <annabrag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 14:15:10 by pmateo            #+#    #+#             */
/*   Updated: 2024/10/31 12:46:14 by annabrag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

	dprintf(2, "PID[%d] | %s\n", getpid(), __func__);
	size = (sizeof(char *) * (__get_env_lst_size(env) + 1));
	tab = yama(CREATE_TAB, NULL, size);
	secure_malloc(tab, true);
	curr = *env;
	i = 0;
	while (curr != NULL)
	{
		tab[i] = ft_strdup(curr->content);
		secure_malloc(tab[i], true);
		i++;
		curr = curr->next;
	}
	tab[i] = NULL;
	return (tab);
}
