/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_exec_tasks.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: art3mis <art3mis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 17:44:18 by art3mis           #+#    #+#             */
/*   Updated: 2024/10/12 01:43:07 by art3mis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	__init_ptrs(t_ptrs *p)
{
	p->new_task = NULL;
	p->i = 0;
	p->size = 0;
}

static void __init_exec(t_ptrs *p)
{
	p->new_task = exec_lst_new_node();
	secure_malloc(p->new_task);
}

static void	__command_case(t_token_dblst *t, t_ptrs *p)
{
	char	*cleaned_token;

	// printf("3\n");
	if (p->new_task->cmd == NULL)
	{
		p->size = (sizeof(char *) * (cmd_token_count(t) + 1));
		p->new_task->cmd = yama(CREATE_TAB, NULL, p->size);
		secure_malloc(p->new_task->cmd);
	}
	cleaned_token = token_cleanup(t->content);
	p->new_task->cmd[p->i] = cleaned_token;
	p->i++;
	if (ft_strchr(cleaned_token, '/') != NULL)
	{
		p->new_task->absolute_path = true;
		p->new_task->bin_path = cleaned_token;
	}
}

static void	__word_case(t_token_dblst *t, t_ptrs *p)
{
	char	*cleaned_token;

	if (p->new_task != NULL)
	{
		cleaned_token = token_cleanup(t->content);
		p->new_task->cmd[p->i] = cleaned_token;
		p->i++;
	}
}

t_exec_lst	*create_new_exec_task(t_data *d)
{
	t_ptrs			p;

	// printf("0\n");
	if (d->token == NULL || d->token->content == NULL)
		return (NULL);
	// printf("1\n");
	__init_ptrs(&p);
	lstclear_exec(&(d->exec));
	printf("----------------------------------- d->exec ------------------------------------\n");
	while (d->token != NULL)
	{
		// printf("2\n");
		if (p.new_task == NULL)
			__init_exec(&p);
		if (d->token->type == COMMAND)
			__command_case(d->token, &p);
		else if (d->token->type == WORD)
			__word_case(d->token, &p);
		d->token = d->token->next;
	}
	// printf("4\n");
	if (p.new_task->cmd != NULL)
	{
		p.new_task->cmd[p.i] = NULL;
		print_tab(p.new_task->cmd);
		// exec_lst_add_back(&(d->exec), p.new_task);
	}
	// printf("5 FINISH\n");
	return (p.new_task);
}

t_exec_lst	*create_exec_tasks2(t_data *d)
{
	t_token_dblst	*head;
	t_exec_lst		*tmp;

	head = d->token;
	// if (create_new_exec_task(d) == FAILURE)
	// 	return (FAILURE);
	tmp = create_new_exec_task(d);
	d->token = head;
	if (create_redir_lst2(d, tmp) == FAILURE)
	{
		printf("redir creation failed\n");
		return (NULL);
	}
	return (tmp);
}

