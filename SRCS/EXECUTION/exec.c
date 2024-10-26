/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmateo <pmateo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 18:16:04 by pmateo            #+#    #+#             */
/*   Updated: 2024/10/26 19:01:59 by pmateo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void	exec(char *path_bin, char **cmd_and_args, char **env)
{
	if (execve(path_bin, cmd_and_args, env) == -1)
	{
		free_and_set_null(path_bin);
		clean_exit_shell(ft_exit_status(FAILURE, ADD));
	}
}

void	go_exec(t_exec_lst *node)
{
	t_data	*d;
	int 	ret;
	char	**env_tab;

	d = data_struct();
	ret = 0;
	env_tab = NULL;
	ret = execute_child_built_in(d, node->cmd);
	dprintf(2, "go_exec | ret = %d\n", ret);
	if (ret != NOT_A_BUILTIN)
		clean_exit_shell(ft_exit_status(0, GET));
	else if (ret == NOT_A_BUILTIN)
	{
		env_tab = recreate_env_tab(&d->env);
		if (handle_bin_path(node, env_tab) == 0)
			exec(node->bin_path, node->cmd, env_tab);
		else
		{
			yama(REMOVE, env_tab, 0);
			clean_exit_shell(ft_exit_status(0, GET));
		}
	}
}
