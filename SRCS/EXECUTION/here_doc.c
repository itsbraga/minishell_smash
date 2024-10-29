/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmateo <pmateo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 19:15:21 by pmateo            #+#    #+#             */
/*   Updated: 2024/10/29 22:11:28 by pmateo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int		wait_heredoc_child(pid_t pid)
{
	int	status;

		// printf("PID : %d | waiting for child... (wait_child)\n", getpid());
	if (waitpid(pid, &status, 0) == -1)
		(err_msg("waitpid", strerror(errno), 0), clean_exit_shell(FAILURE));
	if (WEXITSTATUS(status) == CTRL_C)
	{
		ft_exit_status(130, ADD);
		return (STOP_EXEC);
	}	
	else
		return (SUCCESS);
		// printf("PID : %d | a child is done ! (wait_child)\n", getpid());
}

// static int	__fill_all_heredoc(t_data *d, t_redir_lst *r)
// {
// 	pid_t		pid;
// 	t_redir_lst	*curr;
// 	char		*limiter_w_newline;
// 	int			latest_read_fd;

// 	curr = r;
// 	limiter_w_newline = NULL;
// 	latest_read_fd = 0;
// 	while (curr != NULL)
// 	{
// 		if (curr->type == HERE_DOC)
// 		{
// 			if (latest_read_fd != 0)
// 				close(latest_read_fd);
// 			limiter_w_newline = ft_strjoin(curr->limiter, "\n");
// 			secure_malloc(curr->limiter, true);
// 			latest_read_fd = open_heredoc(d, limiter_w_newline);
// 		}
// 	}
// 		curr = curr->next;
// 		clean_exit_shell(SUCCESS);
// 	}
// 	else
// 		wait_heredoc_child(pid);
// 	return (latest_read_fd);
// }

static int	__fill_all_heredoc(t_data *d, t_redir_lst *r)
{
	pid_t		pid;
	t_redir_lst	*curr;
	char		*limiter_w_newline;
	int			latest_read_fd;

	curr = r;
	limiter_w_newline = NULL;
	latest_read_fd = 0;
	pid = fork();
	if (pid == -1)
		clean_exit_shell(FAILURE);
	else if (pid == 0)
	{
		while (curr != NULL)
		{
			if (curr->type == HERE_DOC)
			{
				if (latest_read_fd != 0)
					close(latest_read_fd);
				limiter_w_newline = ft_strjoin(curr->limiter, "\n");
				secure_malloc(curr->limiter, true);
				latest_read_fd = open_heredoc(d, limiter_w_newline);
			}
		curr = curr->next;
		}
		clean_exit_shell(SUCCESS);
	}
	if (wait_heredoc_child(pid) == STOP_EXEC)
		return (STOP_EXEC);
	else
		return (latest_read_fd);
}

int	handle_heredoc(t_data *d, t_exec_lst **e_lst)
{
	t_exec_lst	*curr;

	curr = *e_lst;
	while (curr != NULL)
	{
		if (curr->heredoc_nb > 0)
		{
			curr->latest_hd = __fill_all_heredoc(d, curr->redir);
			if (curr->latest_hd == STOP_EXEC)
				return (STOP_EXEC);
		}
		curr = curr->next;
	}
	return (SUCCESS);
}
