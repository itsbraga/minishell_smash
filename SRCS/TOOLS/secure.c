/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   secure.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: annabrag <annabrag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 20:30:48 by art3mis           #+#    #+#             */
/*   Updated: 2024/10/24 18:28:17 by annabrag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tools.h"

void	secure_malloc(void *to_secure, bool cleanup)
{
	if (to_secure == NULL)
	{
		// err_msg("malloc", strerror(errno), 0);
		err_msg("malloc", ERR_MALLOC, 0);
		if (cleanup == true)
			clean_exit_shell(FAILURE);
	}
}

void	free_and_set_null(void *to_free)
{
	free(to_free);
	to_free = NULL;
}
