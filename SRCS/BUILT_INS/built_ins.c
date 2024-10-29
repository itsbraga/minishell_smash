/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_ins.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: annabrag <annabrag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 16:20:34 by annabrag          #+#    #+#             */
/*   Updated: 2024/10/29 19:02:49 by annabrag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int	execute_child_built_in(t_data *d, char **cmd)
{
	printf("PID child: %d\n", getpid());
	if (ft_strcmp(cmd[0], "echo") == 0)
		return (ft_echo(cmd));
	else if (ft_strcmp(cmd[0], "pwd") == 0)
		return (ft_pwd());
	else if (ft_strcmp(cmd[0], "env") == 0)
		return (ft_env(d->env, cmd));
	else if (ft_strcmp(cmd[0], "exit") == 0)
		return (ft_exit(cmd));
	else if (ft_strcmp(cmd[0], "export") == 0)
		return (ft_exit_status(SUCCESS, ADD));
	else if (ft_strcmp(cmd[0], "cd") == 0)
		return (ft_exit_status(SUCCESS, ADD));
	else if (ft_strcmp(cmd[0], "unset") == 0)
		return (ft_exit_status(SUCCESS, ADD));
	return (NOT_A_BUILTIN);
}

void	execute_parent_built_in(t_data *d, char **cmd)
{
	printf("PID parent: %d\n", getpid());
	if (ft_strcmp(cmd[0], "export") == 0)
		ft_export(d->exp_env, d->env, cmd);
	else if (ft_strcmp(cmd[0], "cd") == 0)
		ft_cd(d);
	else if (ft_strcmp(cmd[0], "unset") == 0)
		ft_unset(d, cmd);
	else if (ft_strcmp(cmd[0], "exit") == 0)
		ft_exit(cmd);
}

//nous pouvons potentiellement passer tout les builtins executé obligatoirement dans un parent
// en retour de type void car ft_exit_code() renseignera le code erreur
