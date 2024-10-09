/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_env_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: annabrag <annabrag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 12:44:48 by pmateo            #+#    #+#             */
/*   Updated: 2024/10/09 21:24:57 by annabrag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	__cmp_to_equal(const char *s1, const char *s2)
{
	int	i;

	i = 0;
	while (s1[i] == s2[i] && s1[i] && s2[i] && s1[i] != '=' && s2[i] != '=')
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

// TROUVE ET COPIE LA STRING AVEC LE PLUS HAUT CODE ASCII
t_env_lst	*copy_toppest(char **envp)
{
	int		i;
	char	*tmp_top;

	i = 0;
	tmp_top = NULL;
	while (envp[i] != NULL)
	{
		if (tmp_top == NULL)
			tmp_top = envp[0];
		else
		{
			if (__cmp_to_equal(tmp_top, envp[i]) > 0)
				tmp_top = envp[i];
			else
				i++;
		}
	}
	return (env_new_var(tmp_top));
}

// COMPARE LES VALEURS DANS ENV_LIST POUR TROUVER 
// LE DERNIER ELEMENT LE PLUS HAUT DANS L'ORDRE ASCII
t_env_lst	*ascii_sort(char **envp, char *last_added)
{
	int		i;
	char	*tmp;

	i = 0;
	tmp = NULL;
	while (envp[i] != NULL)
	{
		if (__cmp_to_equal(last_added, envp[i]) < 0)
		{
			if (tmp == NULL)
				tmp = envp[i];
			else
			{
				if ((__cmp_to_equal(tmp, envp[i]) > 0)
					&& (__cmp_to_equal(tmp, last_added) != 0))
					tmp = envp[i];
			}
		}
		i++;
	}
	return (env_new_var(tmp));
}
