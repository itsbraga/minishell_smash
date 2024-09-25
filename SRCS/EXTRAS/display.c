/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: annabrag <annabrag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 23:27:17 by art3mis           #+#    #+#             */
/*   Updated: 2024/09/25 14:19:40 by annabrag         ###   ########.fr       */
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

// void    display_main_lst(t_main_lst *main)
// {
// 	t_main_lst    *tmp;

// 	tmp = main;
// 	while (tmp != NULL)
// 	{
// 		ft_printf(STDOUT_FILENO, "%s", BOLD PURPLE "t_main_lst:\t [" R);
// 		ft_printf(STDOUT_FILENO, "%s" BOLD PURPLE "]\n" R, tmp->content);
// 		tmp = tmp->next;
// 	}
// }

void    display_main_lst(t_main_lst *main)
{
	t_main_lst    *tmp;

	tmp = main;
	ft_printf(STDOUT_FILENO, "%s\n", BOLD "-------------------------------------------------" R);
	while (tmp != NULL)
	{
		ft_printf(STDOUT_FILENO, "%s", BOLD PURPLE "t_main_lst:\t [" R);
		ft_printf(STDOUT_FILENO, "%s" BOLD PURPLE "]\n" R, tmp->content);
		tmp = tmp->next;
	}
	ft_printf(STDOUT_FILENO, "%s\n", BOLD "-------------------------------------------------" R);
}

void    display_token_dblst(t_token_dblst *token)
{
	t_token_dblst	*tmp;

	tmp = token;
	while (tmp != NULL)
	{
		ft_printf(STDOUT_FILENO, "%s", BOLD BLUE "t_token_dblst:\t [" R);
		ft_printf(STDOUT_FILENO, "%s" BOLD BLUE "]\n" R, tmp->content);
		ft_printf(STDOUT_FILENO, "%s", YELLOW "token_type:\t ");
		ft_printf(STDOUT_FILENO, "%d\n" R, tmp->type);
		tmp = tmp->next;
	}
}
