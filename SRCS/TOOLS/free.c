/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: annabrag <annabrag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 19:35:38 by annabrag          #+#    #+#             */
/*   Updated: 2024/08/26 17:05:17 by annabrag         ###   ########.fr       */
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

void	del_current_token(t_token **t, t_token *cur)
{
	t_token	*prev;
	t_token	*tmp;

	if (t == NULL || (*t) == NULL || cur == NULL)
		return ;
	prev = NULL;
	tmp = *t;
	if (*t == cur)
	{
		*t = cur->next;
		(free(cur->content), free(cur));
		return ;
	}
	while (tmp != NULL && tmp != cur)
	{
		prev = tmp;
		tmp = tmp->next;
	}
	if (tmp == NULL)
		return ;
	prev->next = cur->next;
	(free(cur->content), free(cur));
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

