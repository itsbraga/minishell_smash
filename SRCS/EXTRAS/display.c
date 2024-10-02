/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: art3mis <art3mis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 23:27:17 by art3mis           #+#    #+#             */
/*   Updated: 2024/10/02 21:50:29 by art3mis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	display_main_lst(t_main_lst *main)
{
	t_main_lst	*tmp;

	tmp = main;
	ft_printf(2, "%s\n", BOLD "=========================================================================" R);
	while (tmp != NULL)
	{
		ft_printf(STDOUT_FILENO, BOLD PURPLE "t_main_lst:\t [" R);
		ft_printf(STDOUT_FILENO, "%s" BOLD PURPLE "]\n" R, tmp->content);
		tmp = tmp->next;
	}
	ft_printf(2, "%s\n", BOLD "=========================================================================" R);
}

static void	__write_type_name(t_token_type type)
{
	ft_printf(STDOUT_FILENO, R "is a ");
	if (type == 0)
		ft_printf(STDOUT_FILENO, RED "[%d ➜  COMMAND]\n" R, type);
	else if (type == 1)
		ft_printf(STDOUT_FILENO, ORANGE "[%d ➜  WORD]\n" R, type);
	else if (type == 2)
		ft_printf(STDOUT_FILENO, YELLOW "[%d ➜  REDIR_IN]\n" R, type);
	else if (type == 3)
		ft_printf(STDOUT_FILENO, GREEN "[%d ➜  INFILE]\n" R, type);
	else if (type == 4)
		ft_printf(STDOUT_FILENO, BLUE "[%d ➜  HERE_DOC]\n" R, type);
	else if (type == 5)
		ft_printf(STDOUT_FILENO, CYAN "[%d ➜  LIMITER]\n" R, type);
	else if (type == 6)
		ft_printf(STDOUT_FILENO, PURPLE "[%d ➜  REDIR_OUT_TRUNC]\n" R, type);
	else if (type == 7)
		ft_printf(STDOUT_FILENO, PINK "[%d ➜  REDIR_OUT_APPEND]\n" R, type);
	else if (type == 8)
		ft_printf(STDOUT_FILENO, GRAY "[%d ➜  OUTFILE]\n" R, type);
	
}

void    display_token_dblst(t_token_dblst *t)
{
	t_token_dblst	*tmp;

	tmp = t;
	while (tmp != NULL)
	{
		ft_printf(STDOUT_FILENO, R BOLD BLUE "t_token_dblst:\t [" R);
		ft_printf(STDOUT_FILENO, "%s" BOLD BLUE "]\n" R, tmp->content);
		if (tmp->type != -1)
		{
			ft_printf(STDOUT_FILENO, YELLOW "token_type:\t ");
			__write_type_name(tmp->type);
		}
		tmp = tmp->next;
	}
}

static void	__display_redir_node(t_redir_lst *node)
{
	ft_printf(2, BP "redir:\t\t [" R "%d" BP "]\n" R, node->type);
	if (node->type == REDIR_IN)
		ft_printf(2, BP "infile:\t\t [" R "%s" BP "]\n" R, node->infile);
	else if (node->type == REDIR_OUT_TRUNC || node->type == REDIR_OUT_APPEND)
		ft_printf(2, BP "outfile:\t [" R "%s" BP "]\n" R, node->outfile);
	else if (node->type == HERE_DOC)
		ft_printf(2, BP "limiter:\t [" R "%s" BP "]\n" R, node->limiter);
}

void	display_redir_lst(t_redir_lst *r)
{
	t_redir_lst *head;

	head = r;
	while (head != NULL)
	{
		__display_redir_node(head);
		head = head->next;
	}
}
