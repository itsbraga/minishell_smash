/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   while_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmateo <pmateo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 18:50:27 by pmateo            #+#    #+#             */
/*   Updated: 2024/10/19 04:35:12 by pmateo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	__wait_child(t_exec_info *info)
{
	int	status;
	int	child_count;

	child_count = info->cmd_count;
	while (child_count != 0)
	{
		printf("PID : %d | waiting for child... (wait_child)\n", getpid());
		if (waitpid(-1, &status, 0) == -1)
		{
			err_msg("waitpid", strerror(errno), 0);
			// clean_exit_shell(FAILURE);
			exit(FAILURE);
		}
		child_count--;
		printf("PID : %d | a child is done ! (wait_child)\n", getpid());
	}
	printf("PID : %d | no more child to wait (wait_child)\n", getpid());
}

static void	__parent(t_exec_info *info)
{
	printf("PID : %d | parent\n", getpid());
	if (info->pipe_count != 0)
	{
		close(info->fd[1]);
		// printf("PID : %d | FD(%d) closed\n", getpid(), info->fd[1]);
		if (info->executed_cmd != 0)
		{
			close(info->old_read_fd);
			// printf("PID : %d | FD(%d) closed\n", getpid(), info->old_read_fd);
		}
		// dprintf(2, "GNL : %s\n", get_next_line(info->fd[0], 0));
		info->old_read_fd = info->fd[0];
		// printf("PID : %d | old_fd contient maintenant ce FD : %d\n", getpid(), info->old_read_fd);
		if (info->executed_cmd == info->cmd_count - 1)
		close(info->fd[0]);
			// printf("PID : %d | FD(%d) closed\n", getpid(), info->fd[0]);
	}
	info->executed_cmd++;
}

void	while_cmd(t_data *d, t_exec_lst **e_lst)
{
	t_exec_lst	*current;
	char		**env_tab;

	current = *e_lst;
	env_tab = recreate_env_tab(&(d->env));
	printf("executed_cmd = %d ; cmd_count = %d\n", d->info->executed_cmd, d->info->cmd_count);
	while ((d->info->executed_cmd != d->info->cmd_count) && current != NULL)
	{
		// printf("début whilecmd\n");
		// printf("current = %p\n", current);
		// printf("current->next = %p\n", current->next);
		if (d->info->pipe_count != 0 && d->info->executed_cmd != d->info->cmd_count - 1)
		{
			if (pipe(d->info->fd) == -1)
				// clean_exit_shell(FAILURE);
				exit(FAILURE);
		}
		d->info->child_pid = fork();
		if (d->info->child_pid == -1)
			// clean_exit_shell(FAILURE);
			exit(FAILURE);
		if (d->info->child_pid == 0)
			pathfinder(d, current, env_tab);
		else
			__parent(d->info);
		current = current->next;
		printf("in loop (while_cmd)\n");
	}
	__wait_child(d->info);
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
//
//