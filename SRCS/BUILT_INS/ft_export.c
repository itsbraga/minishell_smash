/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: annabrag <annabrag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 16:43:03 by annabrag          #+#    #+#             */
/*   Updated: 2024/10/08 15:10:20 by annabrag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// ONLY TO DISPLAY --> BUILT-IN EXPORT STILL TO DO
void    ft_export(t_env_lst *exp_env)
{
    t_env_lst    *tmp;

    tmp = exp_env;
    while (tmp != NULL)
    {
		ft_printf(STDOUT_FILENO, "%s\n", tmp->content);
        tmp = tmp->next;
    }
    // data_struct()->last_exit_status = 0;
}
