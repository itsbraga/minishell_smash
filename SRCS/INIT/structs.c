/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: annabrag <annabrag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 21:37:10 by pmateo            #+#    #+#             */
/*   Updated: 2024/08/26 17:07:40 by annabrag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    init_global(t_global *g)
{
	g->input = NULL;
	g->env = NULL;
	g->token = NULL;
	g->last_exit_status = 0;
}
