/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   while_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: art3mis <art3mis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 18:50:27 by pmateo            #+#    #+#             */
/*   Updated: 2024/09/28 01:06:05 by art3mis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	wait_child(t_exec_info *info)
{
	int	status;

	while (info->cmd_count)
	{
		if (waitpid(-1, &status, 0) == -1)
		{
			err_msg("waitpid", strerror(errno), 0);
			clean_exit_shell(FAILURE);
		}
		info->cmd_count--;
	}
}

void	parent(t_exec_info *info)
{
	
}

void	while_cmd(t_data *d, t_exec_lst **e_lst)
{
	t_exec_lst	*node;
	char		**envtab;

	node = *e_lst;
	envtab = recreate_env_tab(d->env);
	while (d->info.executed_cmd != d->info.cmd_count && node != NULL)
	{
		if (d->info.pipe_count)
			if (pipe(d->info.fd) == -1)
				clean_exit();
		d->info.child_pid = fork();
		if (d->info.child_pid == -1)
			clean_exit();
		if (!d->info.child_pid)
			pathfinder(d, node, envtab);
		else
			parent();
		node = node->next;
		d->info.executed_cmd++;
	}
	wait_child(&d->info);
}

//NOTES :
// - Je dois reperer la presence de pipe, et ne surtout pas en ouvrir si il n'y
//		en a pas.
// - cas d'erreur lorsque chemin relatif et que $PATH n'existe pas
// - Si un segment de commande echoue le message d'erreur ne s'affiche qu'apres
		// l'execution de TOUTE la commande, dans l'ordre des erreurs rencontre.
// - Les heredocs sont ecrits avant toutes choses, et lus au moment du traitement
//		de la commande.
// - Je dois connaitre le nombre exact de here_doc dans une commande
// - Pour les here_doc, besoin de deux fonctions, une principale qui bouclera selon
//		le nombre de here_doc, une seconde qui s'occupe du prompt, et de remplir le fd.
// - ouvrir un pipe -> ecrire dans fd[1] -> fermer fd[1] -> rediriger fd[0] vers STDIN ->
// 		fermer fd[0], rebellotte avec le nombre de here_doc