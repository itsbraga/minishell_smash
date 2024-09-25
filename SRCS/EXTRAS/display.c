/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: annabrag <annabrag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 23:27:17 by art3mis           #+#    #+#             */
/*   Updated: 2024/09/25 20:55:02 by annabrag         ###   ########.fr       */
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

// void	display_main_lst(t_main_lst *main)
// {
// 	t_main_lst	*tmp;

// 	tmp = main;
// 	while (tmp != NULL)
// 	{
// 		ft_printf(STDOUT_FILENO, "%s", BOLD PURPLE "t_main_lst:\t [" R);
// 		ft_printf(STDOUT_FILENO, "%s" BOLD PURPLE "]\n" R, tmp->content);
// 		tmp = tmp->next;
// 	}
// }

void	display_main_lst(t_main_lst *main)
{
	t_main_lst	*tmp;

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

void    display_token_dblst(t_token_dblst *t)
{
	t_token_dblst	*tmp;

	tmp = t;
	while (tmp != NULL)
	{
		ft_printf(STDOUT_FILENO, "%s", BOLD BLUE "t_token_dblst:\t [" R);
		ft_printf(STDOUT_FILENO, "%s" BOLD BLUE "]\n" R, tmp->content);
		ft_printf(STDOUT_FILENO, "%s", YELLOW "token_type:\t ");
		ft_printf(STDOUT_FILENO, "%d\n" R, tmp->type);
		tmp = tmp->next;
	}
}

void	display_redir_node(t_redir_lst *r)
{
	if (r->type == REDIR_IN)
		ft_printf(STDOUT_FILENO, BOLD PINK "infile:\t\t [" R "%s"
BOLD PINK "]\n" R, r->infile);
	else if (r->type == REDIR_OUT_TRUNC)
		ft_printf(STDOUT_FILENO, BOLD PINK "trunc_outfile:\t [" R "%s"
BOLD PINK "]\n" R, r->outfile);
	else if (r->type == REDIR_OUT_APPEND)
		ft_printf(STDOUT_FILENO, BOLD PINK "append_outfile:\t [" R "%s"
BOLD PINK "]\n" R, r->outfile);
	else if (r->type == HERE_DOC)
		ft_printf(STDOUT_FILENO, BOLD PINK "limiter:\t [" R "%s"
BOLD PINK "]\n" R, r->limiter);
}

void	display_redir_lst(t_redir_lst *r)
{
	t_redir_lst *head;

	head = r;
	while (head != NULL)
	{
		ft_printf(2, BOLD PINK "redir:\t\t ["R"%d" BOLD PINK "]\n" R, r->type);
		display_redir_node(head);
		head = head->next;
	}
}
