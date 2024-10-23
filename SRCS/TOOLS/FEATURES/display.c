/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: annabrag <annabrag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 23:27:17 by art3mis           #+#    #+#             */
/*   Updated: 2024/10/23 18:41:09 by annabrag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tools.h"

void	display_main_lst(t_main_lst **main)
{
	t_main_lst	*curr;

	curr = *main;
	ft_printf(STDOUT_FILENO, R BPP LIM " t_main_lst " LIM "\n" R);
	while (curr != NULL)
	{
		ft_printf(STDOUT_FILENO, "--- node ---\n");
		ft_printf(STDOUT_FILENO, BPP "content:\t [" R);
		ft_printf(STDOUT_FILENO, "%s" BPP "]\n" R, curr->content);
		curr = curr->next;
	}
	if (curr == NULL)
		ft_putendl_fd("", STDOUT_FILENO);
}

static void	__write_type_name(t_token_type type)
{
	ft_printf(STDOUT_FILENO, R "is a ");
	if (type == COMMAND)
		ft_printf(STDOUT_FILENO, RED "[%d ➜ COMMAND]\n" R, type);
	else if (type == WORD)
		ft_printf(STDOUT_FILENO, ORANGE "[%d ➜ WORD]\n" R, type);
	else if (type == 2)
		ft_printf(STDOUT_FILENO, YELLOW "[%d ➜ REDIR_IN]\n" R, type);
	else if (type == INFILE)
		ft_printf(STDOUT_FILENO, GREEN "[%d ➜ INFILE]\n" R, type);
	else if (type == 4)
		ft_printf(STDOUT_FILENO, BLUE "[%d ➜ HERE_DOC]\n" R, type);
	else if (type == LIMITER)
		ft_printf(STDOUT_FILENO, CYAN "[%d ➜ LIMITER]\n" R, type);
	else if (type == 6)
		ft_printf(STDOUT_FILENO, PURPLE "[%d ➜ REDIR_OUT_TRUNC]\n" R, type);
	else if (type == 7)
		ft_printf(STDOUT_FILENO, PINK "[%d ➜ REDIR_OUT_APPEND]\n" R, type);
	else if (type == OUTFILE)
		ft_printf(STDOUT_FILENO, LIGHT_GRAY "[%d ➜ OUTFILE]\n" R, type);
}

void	display_token_dblst(t_token_dblst **t)
{
	t_token_dblst	*curr;

	curr = *t;
	ft_printf(STDOUT_FILENO, R BOLD BLUE LIM2 " t_token_dblst " LIM3 "\n" R);
	while (curr != NULL)
	{
		ft_printf(STDOUT_FILENO, "--- node ---\n");
		ft_printf(STDOUT_FILENO, R BOLD BLUE "content:\t [" R);
		ft_printf(STDOUT_FILENO, "%s" BOLD BLUE "]\n" R, curr->content);
		if (curr->type != UNKNOWN)
		{
			ft_printf(STDOUT_FILENO, BLUE "type:\t\t ");
			__write_type_name(curr->type);
		}
		curr = curr->next;
	}
	if (curr == NULL)
		ft_putendl_fd("", STDOUT_FILENO);
}

static void	__display_redir_node(t_redir_lst *node)
{
	ft_printf(1, BP "token type:\t " R);
	if (node->type == REDIR_IN)
	{
		ft_printf(1, BP "[" R "<" BP "]\n" R);
		ft_printf(1, PINK "infile:\t\t [" R "%s" PINK "]\n" R, node->infile);
	}
	else if (node->type == HERE_DOC)
	{
		ft_printf(1, BP "[" R "<<" BP "]\n" R);
		ft_printf(1, PINK "limiter:\t [" R "%s" PINK "]\n" R, node->limiter);
	}
	else if (node->type == REDIR_OUT_TRUNC)
	{
		ft_printf(1, BP "[" R ">" BP "]\n" R);
		ft_printf(1, PINK "outfile:\t [" R "%s" PINK "]\n" R, node->outfile);
	}
	else if (node->type == REDIR_OUT_APPEND)
	{
		ft_printf(1, BP "[" R ">>" BP "]\n" R);
		ft_printf(1, PINK "outfile:\t [" R "%s" PINK "]\n" R, node->outfile);
	}
}

void	display_redir_lst(t_redir_lst **r)
{
	t_redir_lst	*curr;

	curr = *r;
	ft_printf(STDOUT_FILENO, R BP LIM3 " t_redir_lst " LIM "\n" R);
	while (curr != NULL)
	{
		ft_printf(STDOUT_FILENO, "--- node ---\n");
		__display_redir_node(curr);
		curr = curr->next;
	}
}
