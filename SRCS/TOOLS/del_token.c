/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   del_token.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmateo <pmateo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 19:35:38 by annabrag          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2024/08/26 16:11:03 by pmateo           ###   ########.fr       */
=======
/*   Updated: 2024/08/26 16:06:57 by annabrag         ###   ########.fr       */
>>>>>>> 6e6a8733545fee32380e072c25f1579acc0c37b4
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
>>>>>>> 6e6a8733545fee32380e072c25f1579acc0c37b4
