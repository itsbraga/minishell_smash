/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: annabrag <annabrag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 17:53:27 by annabrag          #+#    #+#             */
/*   Updated: 2024/09/25 19:47:06 by annabrag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	__free_data(t_data *d, bool clear_history)
{
	if (d != NULL)
	{
		if (d->prompt != NULL)
			free(d->prompt);
		if (d->main != NULL)
			lstclear_main(&d->main);
		if (d->token != NULL)
			lstclear_token(&d->token);
		if (clear_history == true)
		{
			if (d->env != NULL)
				lstclear_env(&d->env);
			if (d->exp_env != NULL)
				lstclear_env(&d->exp_env);
			rl_clear_history();
		}
		free(d);
	}
}

void	clean_exit_shell(int err_status)
{
	t_data	*d;

	d = get_data_instance();
	if (d != NULL)
		__free_data(d, true);
	yama(CLEAN_ALL, NULL, 0);
	exit(err_status);
}
