/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmateo <pmateo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 19:35:38 by annabrag          #+#    #+#             */
<<<<<<< HEAD:SRCS/TOOLS/free.c
/*   Updated: 2024/08/26 17:05:17 by annabrag         ###   ########.fr       */
=======
<<<<<<< HEAD
/*   Updated: 2024/08/26 16:11:03 by pmateo           ###   ########.fr       */
=======
/*   Updated: 2024/08/26 16:06:57 by annabrag         ###   ########.fr       */
>>>>>>> 6e6a8733545fee32380e072c25f1579acc0c37b4
>>>>>>> 331b04d903f2a2b001b4dd4fcb2fdae6e653d3e1:SRCS/TOOLS/del_token.c
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

// void	del_current_token(t_token **t, t_token *cur)
// {
// 	t_token	*prev;
// 	t_token	*tmp;

<<<<<<< HEAD
// 	if (!t || !(*t) || !cur)
// 		return ;
// 	prev = NULL;
// 	tmp = *t;
// 	if (*t == cur)
// 	{
// 		*t = cur->next;
// 		delone_token(cur);
// 		return ;
// 	}
// 	while (tmp != NULL && tmp != cur)
// 	{
// 		prev = tmp;
// 		tmp = tmp->next;
// 	}
// 	if (!tmp)
// 		return ;
// 	else if (prev != NULL)
// 		prev->next = cur->next;
// 	delone_token(cur);
// }
=======
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
<<<<<<< HEAD:SRCS/TOOLS/free.c

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

=======
>>>>>>> 6e6a8733545fee32380e072c25f1579acc0c37b4
>>>>>>> 331b04d903f2a2b001b4dd4fcb2fdae6e653d3e1:SRCS/TOOLS/del_token.c
