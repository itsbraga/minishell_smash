/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_exec_lst.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: annabrag <annabrag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 17:44:18 by art3mis           #+#    #+#             */
/*   Updated: 2024/10/31 11:24:12 by annabrag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser_lexer.h"

static void	__init_exec(t_ptrs *p)
{
	p->new_task = exec_lst_new_node();
	secure_malloc(p->new_task, true);
}

static void	__command_case(t_token_dblst *t, t_ptrs *p)
{
	char	*cleaned_token;

	if (p->new_task->cmd == NULL)
	{
		p->new_task->cmd = malloc(sizeof(char *) * (cmd_token_count(t) + 1));
		secure_malloc(p->new_task->cmd, true);
	}
	cleaned_token = token_cleanup(ft_strdup(t->content));
	p->new_task->cmd[p->i] = cleaned_token;
	if (ft_strchr(cleaned_token, '/') != NULL)
	{
		p->new_task->is_given_path = true;
		p->new_task->bin_path = cleaned_token;
	}
	p->i++;
}

static void	__word_case(t_token_dblst *t, t_ptrs *p)
{
	char	*cleaned_token;

	if (p->new_task != NULL)
	{
		cleaned_token = token_cleanup(ft_strdup(t->content));
		p->new_task->cmd[p->i] = cleaned_token;
	}
	p->i++;
}

static void	__add_new_task(t_data *d, t_ptrs *p)
{
	if (p->new_task != NULL)
	{
		if (p->new_task->cmd != NULL)
			p->new_task->cmd[p->i] = NULL;
		exec_lst_add_back(&(d->exec), p->new_task);
	}
}

int	create_exec_lst(t_data *d)
{
	t_token_dblst	*curr;
	t_ptrs			p;

	curr = d->token;
	init_ptrs(&p);
	while (curr != NULL)
	{
		if (p.new_task == NULL)
			__init_exec(&p);
		if (curr->type == COMMAND)
			__command_case(curr, &p);
		else if (curr->type == WORD)
			__word_case(curr, &p);
		else if (p.new_task != NULL && curr->type == HERE_DOC)
		{
			p.new_task->heredoc_nb++;
			d->info->all_cmd_heredoc_nb++;
		}
		curr = curr->next;
	}
	__add_new_task(d, &p);
	if (create_redir_lst(d, p.new_task) == FAILURE)
		return (ft_exit_status(FAILURE, ADD));
	return (ft_exit_status(SUCCESS, ADD));
}
