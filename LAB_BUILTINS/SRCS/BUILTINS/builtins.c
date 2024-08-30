/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: annabrag <annabrag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 16:20:34 by annabrag          #+#    #+#             */
/*   Updated: 2024/08/30 18:52:55 by annabrag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "my_builtins.h"

// bool	is_built_in(char *cmd)
// {
// 	int			i;
// 	const char	*built_in[] =
// 	{
// 		"pwd",
// 		"cd",
// 		"env",
// 		"exit"
// 	};

// 	i = 0;
// 	while (built_in[i] != NULL)
// 	{
// 		if (ft_strcmp(built_in[i++], cmd) == 0)
// 			return (true);
// 	}
// 	return (false);
// }

void	exec_built_in(char **built_in, t_global *g)
{
	if ((ft_strcmp(built_in[0], "pwd") == 0)
			|| (ft_strcmp(built_in[0], "/bin/pwd") == 0))
		my_pwd();
	else if ((ft_strcmp(built_in[0], "cd") == 0)
			|| (ft_strcmp(built_in[0], "/bin/cd") == 0))
		my_cd(g);
	else if ((ft_strcmp(built_in[0], "env") == 0)
			|| (ft_strcmp(built_in[0], "/bin/env") == 0))
		my_env(g->env);
	else if (ft_strcmp(built_in[0], "exit") == 0)
		my_exit(g, built_in);
	else if (ft_strcmp(built_in[0], "unset") == 0)
		my_unset(g, built_in + 1);
}
