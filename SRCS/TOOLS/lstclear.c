/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lstclear.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: annabrag <annabrag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 19:35:38 by annabrag          #+#    #+#             */
/*   Updated: 2024/09/25 20:03:01 by annabrag         ###   ########.fr       */
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
		free((*r)->limiter);
		(*r)->limiter = NULL;
		free((*r)->infile);
		(*r)->infile = NULL;
		free((*r)->outfile);
		(*r)->outfile = NULL;
		free(*r);
		(*r) = tmp;
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
