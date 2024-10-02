/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_exec_lst.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: art3mis <art3mis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 17:44:18 by art3mis           #+#    #+#             */
/*   Updated: 2024/10/02 22:38:13 by art3mis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	__init_exec(t_exec_lst *e)
{
	e = yama(CREATE, NULL, sizeof(t_exec_lst));
	secure_malloc(e);
	ft_bzero(e, sizeof(t_exec_lst));
	e->redir = yama(CREATE, NULL, sizeof(t_redir_lst));
	secure_malloc(e->redir);
	ft_bzero(e->redir, sizeof(t_redir_lst));
}

static void	__command_case(t_data *d, t_ptrs *p)
{
	int		size;
	char	*cleaned_token;
	
	size = (sizeof(char *) * cmd_token_count(d->token));
	p->new_task = exec_lst_new_node();
	secure_malloc(p->new_task);
	p->new_task->cmd = yama(CREATE_TAB, NULL, (size + 1));
	secure_malloc(p->new_task->cmd);
	cleaned_token = token_cleanup(d->token->content);
	p->new_task->cmd[p->i] = cleaned_token;
	printf(RED "node_cmd[0]:\t [" R "%s" RED "]\n" R, p->new_task->cmd[p->i]);
	p->i++;
}

static void	__word_case(t_data *d, t_ptrs *p)
{
	int		size;
	char	*cleaned_token;

	if (p->new_task != NULL)
	{
		p->new_task->cmd[p->i] = d->token->content;
		printf(RED "node_cmd[i]:\t [" R "%s" RED "]\n" R, p->new_task->cmd[p->i]);
	}
	else
	{
		d->token->type = COMMAND; // redefini le WORD en COMMAND
		size = (sizeof(char *) * cmd_token_count(d->token));
		p->new_task = exec_lst_new_node();
		secure_malloc(p->new_task);
		p->new_task->cmd = yama(CREATE_TAB, NULL, (size + 1));
		secure_malloc(p->new_task->cmd);
		cleaned_token = token_cleanup(d->token->content);
		p->new_task->cmd[p->i] = cleaned_token;
		printf(RED "node_cmd[x]:\t [" R "%s" RED "]\n" R, p->new_task->cmd[p->i]);	
	}
	p->i++;
}

// manque absolute_path + bin_path
int	create_exec_lst(t_data *d)
{
	t_token_dblst	*head;
	t_ptrs			p;
	
	if (d->token == NULL || d->token->content == NULL)
		return (FAILURE);
	head = d->token;
	__init_exec(d->exec);
	p.new_task = NULL;
	p.i = 0;
	while (d->token != NULL)
	{
		if (d->token->type == COMMAND)
			__command_case(d, &p);
		else if (d->token->type == WORD)
			__word_case(d, &p);
		else if (d->token->type == HERE_DOC)
		{
			d->exec->heredoc_nb++;
			printf(ITAL "heredoc_nb: %d\n" R, d->exec->heredoc_nb);		
		}
		d->token = d->token->next;
		if (d->token == NULL)
			exec_lst_add_back(&(d->exec), p.new_task);
	}
	d->token = head;
	if (create_redir_lst(d) == FAILURE)
		return (err_msg(NULL, "could not create redir_lst", 0), FAILURE);
	return (SUCCESS);
}
