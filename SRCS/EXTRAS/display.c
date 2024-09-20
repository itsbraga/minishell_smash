/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: annabrag <annabrag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 23:27:17 by art3mis           #+#    #+#             */
/*   Updated: 2024/09/20 18:29:23 by annabrag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    display_export_env(t_env_lst *exp_env)
{
	t_env_lst    *tmp;

	tmp = exp_env;
	while (tmp != NULL)
	{
		ft_printf(STDOUT_FILENO, "%s\n", tmp->content);
		tmp = tmp->next;
	}
}

void    display_main_lst(t_main_lst *main)
{
	t_main_lst    *tmp;

	tmp = main;
	while (tmp != NULL)
	{
		ft_printf(STDOUT_FILENO, "%s\t ", BOLD PURPLE "T_MAIN_LST:" RESET);
		ft_printf(STDOUT_FILENO, "|%s|\n", tmp->content);
		tmp = tmp->next;
	}
}
