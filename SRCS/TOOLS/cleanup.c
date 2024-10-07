/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: art3mis <art3mis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 17:53:27 by annabrag          #+#    #+#             */
/*   Updated: 2024/10/07 18:00:38 by art3mis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_data(t_data *d, bool clear_history)
{
	if (d != NULL)
	{
		if (d->prompt != NULL)
			free(d->prompt);
		if (d->main != NULL)
			lstclear_main(&(d->main));
		if (d->token != NULL)
			lstclear_token(&(d->token));
		if (d->exec != NULL)
			lstclear_exec(&(d->exec));
		if (clear_history == true)
		{
			if (d->env != NULL)
				lstclear_env(&(d->env));
			if (d->exp_env != NULL)
				lstclear_env(&(d->exp_env));
			rl_clear_history();
		}
		free(d);
	}
}

void	clean_exit_shell(int err_status)
{
	t_data	*d;

	d = data_struct();
	if (d != NULL)
		free_data(d, true);
	yama(CLEAN_ALL, NULL, 0);
	printf("%s\n", BOLD BLUE BYE_MSG R);
	exit(err_status);
}
