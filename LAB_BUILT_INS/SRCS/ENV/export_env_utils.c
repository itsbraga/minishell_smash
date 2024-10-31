/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_env_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: annabrag <annabrag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 12:44:48 by pmateo            #+#    #+#             */
/*   Updated: 2024/10/30 23:25:46 by annabrag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "my_builtins.h"

int	__cmp_to_equal(const char *s1, const char *s2)
{
	size_t	i;

	i = 0;
	while (s1[i] == s2[i] && s1[i] && s2[i] && s1[i] != '=' && s2[i] != '=')
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

char	*add_quotes_to_value(char *var)
{
	int		i;
	char	*new_str;
	char	*tmp;

	i = 0;
	new_str = malloc((ft_strlen(var) + 3) * sizeof(char));
	if (new_str == NULL)
		exit (FAILURE);
	tmp = var;
	while (*var != '=')
		new_str[i++] = *var++;
	new_str[i++] = *var++;
	new_str[i++] = '"';
	while (*var != '\0')
		new_str[i++] = *var++;
	new_str[i++] = '"';
	new_str[i] = '\0';
	free(tmp);
	return (new_str);
}

t_env_lst	*exp_env_new_var(char *content)
{
	t_env_lst	*new_var;

	new_var = malloc(sizeof(t_env_lst));
	if (new_var == NULL)
		return (NULL);
	new_var->content = ft_strdup(content);
	if (ft_strchr(content, '=') != NULL)
		new_var->content = add_quotes_to_value(new_var->content);
	if (new_var->content == NULL)
	{
		free(new_var->content);
		free(new_var);
		return (NULL);
	}
	new_var->next = NULL;
	return (new_var);
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
	return (exp_env_new_var(tmp_top));
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
	return (exp_env_new_var(tmp));
}
