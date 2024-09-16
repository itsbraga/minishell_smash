/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: annabrag <annabrag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 23:27:17 by art3mis           #+#    #+#             */
/*   Updated: 2024/09/16 16:16:21 by annabrag         ###   ########.fr       */
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

void	display_token_dblst(t_token_dblst *t)
{
	t_token_dblst	*tmp;

	tmp = t;
	while (tmp != NULL)
	{
		ft_putstr_fd(BOLD BLUE "T_TOKEN_DBLST:\t", STDOUT_FILENO);
		ft_putstr_fd(tmp->content, STDOUT_FILENO);
		ft_putendl_fd("", STDOUT_FILENO);
		printf("\t %s:\t%d\n", RESET BOLD YELLOW "type", tmp->type);
		printf(RESET);
		tmp = tmp->next;
	}
}
