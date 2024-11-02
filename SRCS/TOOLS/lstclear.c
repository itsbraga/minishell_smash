/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lstclear.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: art3mis <art3mis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/20 18:49:55 by art3mis           #+#    #+#             */
/*   Updated: 2024/11/02 03:06:33 by art3mis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tools.h"

void	lstclear_main(t_main_lst **main)
{
	t_main_lst	*tmp;

	if (main == NULL || (*main) == NULL)
		return ;
	while ((*main) != NULL)
	{
		tmp = (*main)->next;
		(*main)->next = NULL;
		free_and_set_null((void **)&(*main)->content);
		free(*main);
		(*main) = tmp;
	}
}

void	lstclear_token(t_token_dblst **t)
{
	t_token_dblst	*tmp;

	if (t == NULL || (*t) == NULL)
		return ;
	while ((*t) != NULL)
	{
		tmp = (*t)->next;
		(*t)->next = NULL;
		free_and_set_null((void **)&(*t)->content);
		free(*t);
		(*t) = tmp;
	}
}

void	lstclear_redir(t_redir_lst **r)
{
	t_redir_lst	*tmp;

	if (r == NULL || (*r) == NULL)
		return ;
	while ((*r) != NULL)
	{
		tmp = (*r)->next;
		(*r)->next = NULL;
		if ((*r)->limiter != NULL)
			free_and_set_null((void **)&(*r)->limiter);
		if ((*r)->infile != NULL)
			free_and_set_null((void **)&(*r)->infile);
		if ((*r)->outfile != NULL)
			free_and_set_null((void **)&(*r)->outfile);
		free(*r);
		(*r) = tmp;
	}
}

void	lstclear_exec(t_exec_lst **e)
{
	t_exec_lst	*tmp;

	if (e == NULL || (*e) == NULL)
		return ;
	while ((*e) != NULL)
	{
		tmp = (*e)->next;
		(*e)->next = NULL;
		if ((*e)->redir != NULL)
			lstclear_redir(&((*e)->redir));
		if ((*e)->cmd != NULL)
			free_tab((*e)->cmd);
		free(*e);
		(*e) = tmp;
	}
}

void	lstclear_env(t_env_lst **env)
{
	t_env_lst	*tmp;

	if (env == NULL || (*env) == NULL)
		return ;
	while ((*env) != NULL)
	{
		tmp = (*env)->next;
		(*env)->next = NULL;
		free_and_set_null((void **)&(*env)->content);
		free(*env);
		(*env) = tmp;
	}
}
