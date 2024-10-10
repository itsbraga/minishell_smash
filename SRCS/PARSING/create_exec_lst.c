/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_exec_lst.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: art3mis <art3mis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 17:44:18 by art3mis           #+#    #+#             */
/*   Updated: 2024/10/10 14:28:16 by art3mis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	__init_ptrs(t_ptrs *p)
{
	p->new_task = NULL;
	p->i = 0;
	p->size = 0;
}

static void	__command_case(t_token_dblst *t, t_ptrs *p)
{
	char	*cleaned_token;

	p->size = (sizeof(char *) * (cmd_token_count(t) + 1));
	p->new_task = exec_lst_new_node();
	secure_malloc(p->new_task);
	p->new_task->cmd = yama(CREATE_TAB, NULL, p->size);
	secure_malloc(p->new_task->cmd);
	cleaned_token = token_cleanup(t->content);
	p->new_task->cmd[p->i] = ft_strdup(cleaned_token);
	secure_malloc(p->new_task->cmd[p->i]);
	(void)yama(ADD, (p->new_task->cmd[p->i]), 0);
	if (ft_strchr(cleaned_token, '\'') != NULL)
	{
		p->new_task->absolute_path = true;
		p->new_task->bin_path = cleaned_token;
	}
	p->i++;
}

static void	__word_case(t_token_dblst *t, t_ptrs *p)
{
	char	*cleaned_token;

	if (p->new_task != NULL)
	{
		cleaned_token = token_cleanup(t->content);
		p->new_task->cmd[p->i] = ft_strdup(cleaned_token);
		secure_malloc(p->new_task->cmd[p->i]);
		(void)yama(ADD, (p->new_task->cmd[p->i]), 0);
	}
	p->i++;
}

int	create_exec_lst(t_data *d)
{
	t_token_dblst	*current;
	t_ptrs			p;

	if (d->token == NULL || d->token->content == NULL)
		return (FAILURE);
	current = d->token;
	__init_ptrs(&p);
	lstclear_exec(&(d->exec));
	printf("----------------------------------- d->exec ------------------------------------\n");
	while (d->token != NULL)
	{
		if (d->token->type == COMMAND)
			__command_case(d->token, &p);
		else if (d->token->type == WORD)
			__word_case(d->token, &p);
		d->token = d->token->next;
		if (d->token == NULL)
		{
			p.new_task->cmd[p.i] = NULL;
			print_tab(p.new_task->cmd);
			exec_lst_add_back(&(d->exec), p.new_task);
		}
	}
	d->token = current;
	if (create_redir_lst(d) == FAILURE)
		return (FAILURE);
	display_redir_lst(d->exec->redir);
	return (SUCCESS);
}

// int	create_exec_lst(t_data *d)
// {
// 	t_token_dblst	*current;
// 	t_ptrs			p;

// 	if (d->token == NULL || d->token->content == NULL)
// 		return (FAILURE);
// 	current = d->token;
// 	__init_ptrs(&p);
// 	lstclear_exec(&(d->exec));
// 	printf("----------------------------------- d->exec ------------------------------------\n");
// 	while (d->token != NULL)
// 	{
// 		if (d->token->type == COMMAND)
// 			__command_case(d->token, &p);
// 		else if (d->token->type == WORD)
// 			__word_case(d->token, &p);
// 		else if (IS_REDIR(d->token->type))
// 		{
// 			d->token = current;
// 			if (create_redir_lst(d) == FAILURE)
// 				return (err_msg(NULL, "could not create redir_lst", 0), FAILURE);
// 		}
// 		d->token = d->token->next;
// 		if (d->token == NULL)
// 		{
// 			p.new_task->cmd[p.i] = NULL;
// 			print_tab(p.new_task->cmd);
// 			exec_lst_add_back(&(d->exec), p.new_task);
// 		}
// 	}
// 	return (SUCCESS);
// }
