/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: annabrag <annabrag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 19:35:38 by annabrag          #+#    #+#             */
/*   Updated: 2024/08/29 18:08:44 by annabrag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "my_builtins.h"

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
        *env = tmp;
    }
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
		free(*t);
		(*t) = tmp;
	}
	(*t) = NULL;
}

// void	lstclear_input(t_input **input)
// {
// 	t_input	*tmp;
	
// 	if (input == NULL || (*input) == NULL)
// 		return ;
// 	while ((*input) != NULL)
// 	{
// 		tmp = (*input)->next;
// 		free((*input)->content); 
// 		free(*input);
// 		(*input) = tmp;
// 	}
// 	(*input) = NULL;
// }

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
    if (g != NULL && g->token != NULL)
        lstclear_tokens(&g->token);
    if (clear_history == true)
    {
        if (g != NULL && g->env != NULL)
            lstclear_env(&g->env);
        rl_clear_history();
    }
}

// void    free_global(t_global *g, bool clear_history)
// {
//     if (g != NULL && g->input != NULL)
//         lstclear_input(g->input);
// 	if (g != NULL && g->cmd != NULL)
// 		//
//     if (g != NULL && g->token != NULL)
//         lstclear_token(&g->token);
//     if (clear_history == true)
//     {
//         if (g != NULL && g->env != NULL)
//             lstclear_env(g->env);
//         rl_clear_history();
//     }
// }

