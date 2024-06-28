/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmateo <pmateo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 13:59:53 by pmateo            #+#    #+#             */
/*   Updated: 2024/06/28 15:21:39 by pmateo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../INCLUDES/minishell.h"

void    expand_token(t_global *g, t_token *current)
{
    int     i;
    char    *match;
    char    *to_find;

    i = 0;
    match = NULL;
    
    
    
}

void    handle_expansion(t_global *g)
{
    t_token *current;
    
    current = g->token;
    while (current->content)
    {
        if (current->to_expand)
        {
            expand_token(g, current);            
        }
        else
            current = current->next;
    }    
}