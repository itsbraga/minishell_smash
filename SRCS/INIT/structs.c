/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: annabrag <annabrag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 21:37:10 by pmateo            #+#    #+#             */
/*   Updated: 2024/08/13 15:35:42 by annabrag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    init_global(t_global *g)
{
	g->input = NULL;
	g->env = NULL;
	g->export_env = NULL;
}

void	init_token(t_token *t)
{
		t->idx = 0;
		t->to_expand = false;
		t->s_quoted = false;
		t->db_quoted = false;
		t->t_quoted = 0;
		t->content = NULL;
}