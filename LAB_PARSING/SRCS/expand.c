/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmateo <pmateo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 20:42:03 by pmateo            #+#    #+#             */
/*   Updated: 2024/07/03 20:46:01 by pmateo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../INCLUDES/mini_parsing.h"

// Le flag "to_expand" ne doit etre mis a 1 selon deux facteurs, si le parser a rencontre un $
// en debut de string, et 
// void    handle_expansion(t_token *t)
// {
// 	t_token *current;
	
// 	current = g->token;
// 	while (current->content)
// 	{
// 		if (current->to_expand)
// 		{
// 			if (current->t_quoted != D_QUOTE_INSIDE)
// 				expand_token(g, current);  
// 		}
// 		else
// 			current = current->next;
// 	}    
// }

void	expand_token(t_token **tok, char **envp)
{
	t_token *current;

	current = *tok;
	while (current->next != NULL)
	{
		assign_token(current);
		current = current->next;
	}
}