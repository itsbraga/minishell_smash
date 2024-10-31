/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: annabrag <annabrag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 21:37:10 by pmateo            #+#    #+#             */
/*   Updated: 2024/09/20 14:54:04 by annabrag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// singleton version
t_data	*data_struct(void)
{
	static t_data	*instance = NULL;
	t_prompt		pr;

	if (instance == NULL)
	{
		instance = yama(CREATE, NULL, sizeof(t_data));
		secure_malloc(instance, true);
		instance->prompt = generate_prompt(&pr, instance);
		secure_malloc(instance->prompt, true);
		instance->fd_stdin_backup = 0;
		instance->main = NULL;
		instance->token = NULL;
		instance->exec = NULL;
		instance->info = NULL;
		instance->env = NULL;
		instance->exp_env = NULL;
	}
	return (instance);
}
