/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: art3mis <art3mis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 23:27:17 by art3mis           #+#    #+#             */
/*   Updated: 2024/09/15 22:48:11 by art3mis          ###   ########.fr       */
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
		ft_putstr_fd(BOLD PURPLE "T_MAIN_LST: " RESET, STDOUT_FILENO);
		ft_putstr_fd(tmp->content, STDOUT_FILENO);
		ft_putendl_fd("", STDOUT_FILENO);
		tmp = tmp->next;
	}
}

void	display_token_dblst(t_token_dblst *t)
{
	t_token_dblst	*tmp;

	tmp = t;
	while (tmp != NULL)
	{
		ft_putstr_fd(RESET BOLD BLUE "t_token_dblst: " RESET, STDOUT_FILENO);
		ft_putstr_fd(tmp->content, STDOUT_FILENO);
		ft_putendl_fd("", STDOUT_FILENO);
		printf("\t %s: %d\n", BOLD YELLOW "type", tmp->type);
		tmp = tmp->next;
	}
}
