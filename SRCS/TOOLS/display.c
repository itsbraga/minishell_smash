/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: annabrag <annabrag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 23:27:17 by art3mis           #+#    #+#             */
/*   Updated: 2024/09/02 16:45:51 by annabrag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    display_export_env(t_env *exp_env)
{
    t_env    *tmp;

    tmp = exp_env;
    while (tmp != NULL)
    {
        ft_putstr_fd(tmp->content, 1);
        ft_putendl_fd("", 1);
        tmp = tmp->next;
    }
}

void	display_tokens(t_token *t)
{
	t_token	*tmp;

	tmp = t;
	while (tmp != NULL)
	{
		ft_putstr_fd(tmp->content, 1);
		ft_putendl_fd("", 1);
		tmp = tmp->next;
	}
}

void    display_main_lst(t_main_lst *main)
{
    t_main_lst    *tmp;

    tmp = main;
    while (tmp != NULL)
    {
        ft_putstr_fd(tmp->content, 1);
        ft_putendl_fd("", 1);
        tmp = tmp->next;
    }
}
