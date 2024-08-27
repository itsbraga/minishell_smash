/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: art3mis <art3mis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 19:35:38 by annabrag          #+#    #+#             */
/*   Updated: 2024/08/27 02:26:59 by art3mis          ###   ########.fr       */
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

