/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   secure_malloc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: art3mis <art3mis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 22:37:15 by art3mis           #+#    #+#             */
/*   Updated: 2024/09/27 22:39:09 by art3mis          ###   ########.fr       */
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
