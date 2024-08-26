/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   old_create_env.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmateo <pmateo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 04:28:04 by pmateo            #+#    #+#             */
/*   Updated: 2024/08/26 16:04:52 by pmateo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//REMPLIS L'ENVIRONNEMENT DE EXPORT ENV AVEC UN ORDRE ASCII 

// static void	__fill_export_env(t_global *g, size_t exp_env_size, size_t envp_size)
// {	
// 	while (exp_env_size != envp_size)
// 	{
// 		if (!exp_env_size)
// 			copy_toppest(g);
// 		else
// 			alpha_sort(g, g->exp_env[exp_env_size - 1], exp_env_size);
// 		exp_env_size++;
// 	}
// 	g->export_env[envp_size] = NULL;
// }

// void	create_env(t_global *g, char **envp)
// {
// 	int		i;
// 	size_t	envp_size;
// 	char 	**minishell_env;

// 	i = 0;
// 	envp_size = get_env_size(envp);
// 	minishell_env = malloc((envp_size + 1) * sizeof(char *));
// 	while (envp[i])
// 	{
// 		minishell_env[i] = ft_strdup(envp[i]);
// 		i++;
// 	}
// 	g->env = minishell_env;
// 	g->export_env = malloc((envp_size + 1) * sizeof(char *));
// 	__fill_export_env(g, 0, envp_size);
// }
