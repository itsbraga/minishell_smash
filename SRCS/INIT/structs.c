/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmateo <pmateo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 21:37:10 by pmateo            #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2024/08/26 17:07:40 by annabrag         ###   ########.fr       */
=======
/*   Updated: 2024/08/26 18:26:10 by pmateo           ###   ########.fr       */
>>>>>>> 331b04d903f2a2b001b4dd4fcb2fdae6e653d3e1
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

<<<<<<< HEAD
=======
// static void	__init_token(t_token *t)
// {
// 	t->content = NULL;
// }

>>>>>>> 331b04d903f2a2b001b4dd4fcb2fdae6e653d3e1
void    init_global(t_global *g)
{
	g->input = NULL;
	g->env = NULL;
<<<<<<< HEAD
	g->token = NULL;
=======
	g->exp_env = NULL;
	g->token = NULL;
	// __init_token(g->token);
>>>>>>> 331b04d903f2a2b001b4dd4fcb2fdae6e653d3e1
	g->last_exit_status = 0;
}
