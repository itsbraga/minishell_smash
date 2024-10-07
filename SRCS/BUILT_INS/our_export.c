/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   our_export.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: art3mis <art3mis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 16:43:03 by annabrag          #+#    #+#             */
/*   Updated: 2024/10/07 21:11:38 by art3mis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// ONLY TO DISPLAY --> BUILT-IN EXPORT STILL TO DO
void    our_export(t_env_lst *exp_env)
{
    t_env_lst    *tmp;

    tmp = exp_env;
    while (tmp != NULL)
    {
		ft_printf(STDOUT_FILENO, "%s\n", tmp->content);
        tmp = tmp->next;
    }
}
