/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: annabrag <annabrag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 04:28:04 by pmateo            #+#    #+#             */
/*   Updated: 2024/08/20 20:32:25 by annabrag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "built_ins.h"

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
// }

void	create_env_list(t_env *env, char **envp)
{
	int		i;
	t_env	*var;

	i = 0;
	while (envp[i] != NULL)
	{
		var = e_new_node(envp[i]);
		if (var == NULL)
			return ;
		e_add_back(&env, var);
		i++;
	}
}

void	display_env(t_env *env)
{
	t_env	*tmp;

	tmp = env;
	while (tmp != NULL)
	{
		ft_putstr_fd(tmp->content, 1);
		ft_putendl_fd("", 1);
		tmp = tmp->next;
	}
}
