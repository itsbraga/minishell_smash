/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   secure_malloc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: annabrag <annabrag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 22:37:15 by art3mis           #+#    #+#             */
/*   Updated: 2024/10/09 21:34:39 by annabrag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	secure_malloc(void *to_secure)
{
	if (to_secure == NULL)
	{
		err_msg("malloc", ERR_MALLOC, 0);
		clean_exit_shell(FAILURE);
	}
}

void	secure_malloc2(void *to_secure, bool full_clean)
{
	if (to_secure == NULL)
	{
		if (full_clean == true)
			clean_exit_shell(FAILURE);
		else
		{
			free_data(data_struct(), false);
			exit(FAILURE);
		}
	}
}
