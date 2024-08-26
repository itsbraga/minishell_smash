/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmateo <pmateo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 21:37:10 by pmateo            #+#    #+#             */
/*   Updated: 2024/08/26 18:26:10 by pmateo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// static void	__init_token(t_token *t)
// {
// 	t->content = NULL;
// }

void    init_global(t_global *g)
{
	g->input = NULL;
	g->env = NULL;
	g->exp_env = NULL;
	g->token = NULL;
	// __init_token(g->token);
	g->last_exit_status = 0;
}
