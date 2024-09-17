/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: art3mis <art3mis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 23:27:17 by art3mis           #+#    #+#             */
/*   Updated: 2024/09/17 18:36:52 by art3mis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    display_export_env(t_env_lst *exp_env)
{
	t_env_lst    *tmp;

	tmp = exp_env;
	while (tmp != NULL)
	{
		ft_putstr_fd(tmp->content, STDOUT_FILENO);
		ft_putendl_fd("", STDOUT_FILENO);
		tmp = tmp->next;
	}
}

void    display_main_lst(t_main_lst *main)
{
	t_main_lst    *tmp;

	tmp = main;
	while (tmp != NULL)
	{
		ft_putstr_fd(BOLD PURPLE "T_MAIN_LST:\t" RESET, STDOUT_FILENO);
		ft_putstr_fd(tmp->content, STDOUT_FILENO);
		ft_putendl_fd("", STDOUT_FILENO);
		tmp = tmp->next;
	}
}
