/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: annabrag <annabrag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 19:35:38 by annabrag          #+#    #+#             */
/*   Updated: 2024/09/19 18:52:23 by annabrag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

void	lstclear_tokens(t_token_dblst **t)
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

void	free_global(t_global *g, bool clear_history)
{
	if (g != NULL && g->prompt != NULL)
		free(g->prompt);
	if (g != NULL && g->main != NULL)
		lstclear_main(&g->main);
	if (g != NULL && g->token != NULL)
		lstclear_tokens(&g->token);
	if (clear_history == true)
	{
		if (g != NULL && g->env != NULL)
			lstclear_env(&g->env);
		if (g != NULL && g->exp_env != NULL)
			lstclear_env(&g->exp_env);
		rl_clear_history();
	}
}
