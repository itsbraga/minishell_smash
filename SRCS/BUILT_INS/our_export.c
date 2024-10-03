/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   our_export.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: art3mis <art3mis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 16:43:03 by annabrag          #+#    #+#             */
/*   Updated: 2024/10/03 23:20:54 by art3mis          ###   ########.fr       */
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
        ft_putstr_fd(tmp->content, 1);
        ft_putendl_fd("", 1);
        tmp = tmp->next;
    }
}
