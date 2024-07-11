/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: panther <panther@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 13:59:53 by pmateo            #+#    #+#             */
/*   Updated: 2024/07/11 15:50:53 by panther          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../INCLUDES/minishell.h"

void    expand_token(t_global *g, t_token *current)
{
	int     i;
	char    *match;
	char    *to_find;

	i = 0;
	match = NULL;
	
	
	
}
// Le flag "to_expand" ne doit etre mis a 1 selon deux facteurs, si le parser a rencontre un $
// en debut de string, et 
void    handle_expansion(t_global *g)
{
	t_token *current;
	
	current = g->token;
	while (current->content)
	{
		if (current->to_expand)
		{
			if (current->t_quoted != D_QUOTE_INSIDE)
				expand_token(g, current);  
		}
		else
			current = current->next;
	}    
}