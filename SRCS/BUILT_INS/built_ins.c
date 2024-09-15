/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_ins.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: art3mis <art3mis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 16:20:34 by annabrag          #+#    #+#             */
/*   Updated: 2024/09/15 23:39:13 by art3mis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_built_in(char *cmd)
{
	size_t		i;
	const char	*built_in[] =
	{
		"pwd",
		"cd",
		"env",
		// "export",
		"unset",
		"exit"
	};

	i = 0;
	while (built_in[i] != NULL)
	{
		if (ft_strcmp(built_in[i++], cmd) == 0)
			return (true);
	}
	return (false);
}

void	exec_built_in(char **cmd, t_global *g)
{
	if (ft_strcmp(cmd[0], "pwd") == 0)
		my_pwd();
	else if (ft_strcmp(cmd[0], "cd") == 0)
		my_cd(g);
	else if (ft_strcmp(cmd[0], "env") == 0)
	{
		if (cmd[1] != NULL)
			return (err_msg(cmd[1], "No such file or directory", 1));
		my_env(g->env);
	}
	else if (ft_strcmp(cmd[0], "exit") == 0)
		my_exit(g, cmd);
	else if (ft_strcmp(cmd[0], "unset") == 0)
		my_unset(g, cmd + 1);
	else if (ft_strcmp(cmd[0], "clear") == 0)
		printf("\033[H\033[J");
}
