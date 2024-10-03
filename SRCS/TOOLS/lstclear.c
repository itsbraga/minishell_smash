/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lstclear.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: art3mis <art3mis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 19:35:38 by annabrag          #+#    #+#             */
/*   Updated: 2024/10/03 23:27:17 by art3mis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	lstclear_main(t_main_lst **main)
{
	t_main_lst	*tmp;
	
	if (main == NULL || (*main) == NULL)
		return ;
	while ((*main) != NULL)
	{
		tmp = (*main)->next;
		(*main)->next = NULL;
		free((*main)->content); 
		(*main)->next = NULL;
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
		free((*t)->content);
		(*t)->content = NULL;
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
		{
			free((*r)->limiter);
			(*r)->limiter = NULL;
		}
		if ((*r)->infile != NULL)
		{
			free((*r)->infile);
			(*r)->infile = NULL;
		}
		if ((*r)->outfile != NULL)
		{
			free((*r)->outfile);
			(*r)->outfile = NULL;
		}
		free(*r);
		(*r) = tmp;
	}
}

void	lstclear_exec(t_exec_lst **e)
{
	t_exec_lst	*tmp;
	int			i;
	
	if (e == NULL || (*e) == NULL)
		return ;
	while ((*e) != NULL)
	{
		tmp = (*e)->next;
		(*e)->next = NULL;
		if ((*e)->redir != NULL)
			lstclear_redir(&((*e)->redir));
		free((*e)->bin_path);
		(*e)->bin_path = NULL;
		if ((*e)->cmd != NULL)
		{
			i = 0;
			free((*e)->cmd[i]);
			(*e)->cmd[i] = NULL;
			i++;
		}
		free((*e)->cmd);
		(*e)->cmd = NULL;
		free(*e);
		(*e) = tmp;
	}
}

void	lstclear_env(t_env_lst **env)
{
	t_env_lst *tmp;

	if (env == NULL || (*env) == NULL)
		return ;
	while ((*env) != NULL)
	{
		tmp = (*env)->next;
		(*env)->next = NULL;
		free((*env)->content);
		(*env)->content = NULL;
		free(*env);
		(*env) = tmp;
	}
}
