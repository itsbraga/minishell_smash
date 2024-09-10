/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: art3mis <art3mis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 19:35:38 by annabrag          #+#    #+#             */
/*   Updated: 2024/09/10 19:06:36 by art3mis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	lstclear_env(t_env **env)
{
    t_env *tmp;

    if (env == NULL || (*env) == NULL)
        return ;
    while ((*env) != NULL)
    {
        tmp = (*env)->next;
        free((*env)->content);
        free(*env);
        (*env) = tmp;
    }
	(*env) = NULL;
}

void	lstclear_tokens(t_token **t)
{
	t_token	*tmp;
	
	if (t == NULL || (*t) == NULL)
		return ;
	while ((*t) != NULL)
	{
		tmp = (*t)->next;
		free((*t)->content);
		free((*t)->type);
		free(*t);
		(*t) = tmp;
	}
	(*t) = NULL;
}

void	lstclear_main(t_main_lst **main)
{
	t_main_lst	*tmp;
	
	if (main == NULL || (*main) == NULL)
		return ;
	while ((*main) != NULL)
	{
		tmp = (*main)->next;
		free((*main)->content); 
		free(*main);
		(*main) = tmp;
	}
	(*main) = NULL;
}

void	free_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i] != NULL)
	{
		free(tab[i]);
		i++;
	}
	free(tab);
	tab = NULL;
}

void    free_global(t_global *g, bool clear_history)
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
        rl_clear_history();
    }
}
