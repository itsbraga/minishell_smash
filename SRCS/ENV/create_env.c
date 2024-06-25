/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmateo <pmateo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 04:28:04 by pmateo            #+#    #+#             */
/*   Updated: 2024/06/25 20:00:36 by pmateo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../INCLUDES/minishell.h"

// int	cmp_to_equal(const char *s1, const char *s2)
// {
// 	size_t	i;

// 	i = 0;
// 	while (s1[i] == s2[i] && s1[i] && s2[i] && s1[i] != '=' && s2[i] != '=')
// 		i++;
// 	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
// }

size_t	get_env_size(char **envp)
{
	size_t	size;
	
	size = 0;
	while (envp[size])
		size++;
	return (size);
}

char	**create_env(char **envp)
{
	int		i;
	size_t	env_size;
	char 	**minishell_env;

	i = 0;
	env_size = get_env_size(envp); 
	minishell_env = malloc((env_size + 1) * sizeof(char *));
	while (envp[i])
	{
		minishell_env[i] = ft_strdup(envp[i]);
		i++;
	}
	return (minishell_env);
}

// char *alpha_sort(char **envp)
// {
// 	int	i;
// 	char *tmp_top;

// 	i = 0;
// 	tmp_top = NULL;
// 	while(envp[i])
// 	{
// 		if (!tmp_top)
// 			tmp_top = envp[i];
// 		else
// 		{
// 			if (envp[i][0] > tmp_top[0])
// 				tmp_top = envp[i];
// 		}
// 		i++;
// 	}
// 	return ( )
// }

// char	**create_env_export(char **envp, size_t	env_size)
// {
// 	size_t	env_size;
// 	char **export_env;
// 	char *lastest;

// 	env_size -= 1;
// 	export_env = malloc((env_size + 1) * sizeof(char *));
// 	lastest = NULL;
// 	while (envp[env_size])
// 	{
// 		if (!lastest)
// 			lastest = envp[env_size];
// 		else
// 		{
// 			if (cmp_to_equal(envp[env_size], lastest))
// 		}
// 		env_size--;
// 	}	

	
// }