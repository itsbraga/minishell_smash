/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_exit_shell.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: annabrag <annabrag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 17:53:27 by annabrag          #+#    #+#             */
/*   Updated: 2024/09/19 16:01:55 by annabrag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	clean_exit_shell(t_global *g, int err_status)
{
	if (g != NULL)
		free_global(g, true);
	yama(CLEAN_ALL, NULL, 0);
	exit(err_status);
}
