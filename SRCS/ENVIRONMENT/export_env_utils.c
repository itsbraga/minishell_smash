/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_env_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: annabrag <annabrag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 12:44:48 by pmateo            #+#    #+#             */
/*   Updated: 2024/11/02 21:09:57 by annabrag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	cmp_to_equal(const char *s1, const char *s2)
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
			if (cmp_to_equal(tmp_top, envp[i]) > 0)
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
		if (cmp_to_equal(last_added, envp[i]) < 0)
		{
			if (tmp == NULL)
				tmp = envp[i];
			else
			{
				if ((cmp_to_equal(tmp, envp[i]) > 0)
					&& (cmp_to_equal(tmp, last_added) != 0))
					tmp = envp[i];
			}
		}
		i++;
	}
	return (exp_env_new_var(tmp));
}

/*	**	Instead of freeing var (the initial content),
	we leave that responsibility to the caller.
	
	**	add_quotes_to_value now simply returns new_str,
	allowing the caller to manage the memory more
	explicitly.
*/
char	*add_quotes_to_value(char *content)
{
	int		i;
	int		j;
	char	*new_str;

	i = 0;
	j = 0;
	new_str = malloc(sizeof(char) * (ft_strlen(content) + 3));
	secure_malloc(new_str, true);
	while (content[j] != '=')
		new_str[i++] = content[j++];
	new_str[i++] = content[j++];
	new_str[i++] = '"';
	while (content[j] != '\0')
		new_str[i++] = content[j++];
	new_str[i++] = '"';
	new_str[i] = '\0';
	return (new_str);
}

t_env_lst	*exp_env_new_var(char *content)
{
	t_env_lst	*new_var;

	new_var = malloc(sizeof(t_env_lst));
	secure_malloc(new_var, true);
	if (ft_strchr(content, '=') == NULL)
	{
		new_var->content = ft_strdup(content);
		secure_malloc(new_var->content, true);
	}
	else
	{
		new_var->content = add_quotes_to_value(content);
		secure_malloc(new_var->content, true);
	}
	new_var->next = NULL;
	return (new_var);
}
