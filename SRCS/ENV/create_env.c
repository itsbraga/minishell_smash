/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmateo <pmateo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 04:28:04 by pmateo            #+#    #+#             */
/*   Updated: 2024/06/24 08:10:34 by pmateo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../INCLUDES/minishell.h"

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

// char	**create_env_export(char **envp)
// {
// 	int	i;
// 	size_t	env_size;
// 	char	**minishell_env;
// }