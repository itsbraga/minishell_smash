/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: annabrag <annabrag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 21:37:10 by pmateo            #+#    #+#             */
/*   Updated: 2024/08/28 14:26:56 by annabrag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*__generate_prompt(void)
{
	char	*username;
	char	*rb_username;
	char	*part1;
	char	*prompt;
	
	username = getenv("USER");
	if (username == NULL)
		username = "unknown";
	rb_username = rainbow_prompt(username);
	part1 = ft_strjoin(BOLD "[", rb_username);
	free(rb_username);
	prompt = ft_strjoin(part1, BOLD "@42]" RESET " $> ");
	free(part1);
	return (prompt);
}

void    init_global(t_global *g)
{
	g->prompt = __generate_prompt();
	if (g->prompt == NULL)
		(free(g->prompt), exit(FAILURE));
	g->input = NULL;
	g->env = NULL;
	g->exp_env = NULL;
	g->token = NULL;
	g_last_exit_status = 0;
}
