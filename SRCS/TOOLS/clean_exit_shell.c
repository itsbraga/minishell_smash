/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_exit_shell.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: annabrag <annabrag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 17:53:27 by annabrag          #+#    #+#             */
/*   Updated: 2024/09/20 17:15:22 by annabrag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	clean_exit_shell(int err_status)
{
	t_data	*d;

	d = get_data_instance();
	if (d != NULL)
		free_data(d, true);
	yama(CLEAN_ALL, NULL, 0);
	exit(err_status);
}
