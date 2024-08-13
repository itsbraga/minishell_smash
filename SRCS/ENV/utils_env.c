/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: annabrag <annabrag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 14:15:10 by pmateo            #+#    #+#             */
/*   Updated: 2024/08/13 14:34:19 by annabrag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	cmp_to_equal(const char *s1, const char *s2)
{
	size_t	i;

	i = 0;
	while (s1[i] == s2[i] && s1[i] && s2[i] && s1[i] != '=' && s2[i] != '=')
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

size_t	get_env_size(char **envp)
{
	size_t	size;
	
	size = 0;
	while (envp[size])
		size++;
	return (size);
}

void	copy_toppest(t_global *g)
{
	int	i;
	char *tmp_top;

	i = 0;
	tmp_top = NULL;
	while (g->env[i])
	{
		if (!tmp_top)
			tmp_top = g->env[0];
		else
		{
			if (cmp_to_equal(tmp_top, g->env[i] ) > 0)
				tmp_top = g->env[i];
			else
				i++;
		}
	}
	g->export_env[0] = ft_strdup(tmp_top);
}

void	alpha_sort(t_global *g, char *current, size_t exp_env_index)
{
	int	i;
	char *tmp;

	i = 0;
	tmp = NULL;
	while(g->env[i])
	{
		if (cmp_to_equal(current, g->env[i]) < 0)
		{
			if (!tmp)
				tmp = g->env[i];
			else
			{
				if ((cmp_to_equal(tmp, g->env[i]) > 0)
						&& (cmp_to_equal(tmp, current) != 0))
					tmp = g->env[i];
			}	
		}
		i++;
	}
	g->export_env[exp_env_index] = ft_strdup(tmp);
}