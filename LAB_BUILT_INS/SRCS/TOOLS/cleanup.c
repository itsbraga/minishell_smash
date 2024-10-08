/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: annabrag <annabrag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 19:35:38 by annabrag          #+#    #+#             */
/*   Updated: 2024/10/08 16:56:29 by annabrag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "my_builtins.h"

void	lstclear_env(t_env_lst **env)
{
    t_env_lst *tmp;

    if (env == NULL || (*env) == NULL)
        return ;
    while ((*env) != NULL)
    {
        tmp = (*env)->next;
        free((*env)->content);
        free(*env);
        *env = tmp;
    }
}

void	lstclear_token(t_token **t)
{
	t_token	*tmp;
	
	if (t == NULL || (*t) == NULL)
		return ;
	while ((*t) != NULL)
	{
		tmp = (*t)->next;
		free((*t)->content); 
		free(*t);
		(*t) = tmp;
	}
	(*t) = NULL;
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
	if (g != NULL)
	{
		if (g->prompt != NULL)
			free(g->prompt);
		if (g->input != NULL)
			free(g->input);
		if (g->token != NULL)
			lstclear_token(&g->token);
		if (clear_history == true)
		{
			if (g->env != NULL)
				lstclear_env(&g->env);
			if (g->exp_env != NULL)
				lstclear_env(&g->env);
			rl_clear_history();
		}
	}
}

