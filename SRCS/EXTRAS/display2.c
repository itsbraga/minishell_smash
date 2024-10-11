/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: art3mis <art3mis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 20:56:55 by annabrag          #+#    #+#             */
/*   Updated: 2024/10/12 01:47:03 by art3mis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	display_exec_lst(t_exec_lst *e)
{
	t_exec_lst	*current;

	current = e;
	ft_printf(STDOUT_FILENO, R BOLD Y LIM " t_exec_lst " LIM "\n" R);
	while (current != NULL)
	{
		ft_printf(1, "--- NODE ---\n");
		ft_printf(1, Y "heredoc_nb:\t [" R "%d" Y "]\n" R, current->heredoc_nb);
		ft_printf(1, Y "absolute_path:\t [" R);
		ft_printf(1, "%d" Y "]\n" R, current->absolute_path);
		ft_printf(1, Y "bin_path:\t [" R "%s" Y "]\n" R, current->bin_path);
		if (current->cmd != NULL)
			print_tab(current->cmd);
		else
			ft_printf(1, Y "cmd:\t\t [" R "(null)" Y "]\n" R);
		if (current->redir != NULL)
			display_redir_lst(current->redir);
		else
			ft_printf(1, BOLD Y "t_redir_lst:\t [" R "(null)" BOLD Y "]\n" R);
		current = current->next;
	}
	if (current == NULL)
		ft_putendl_fd("", STDOUT_FILENO);
}

void	print_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i] != NULL)
	{
		dprintf(2, BOLD GREEN "tab[i]: " R "%s" GREEN " ; " R, tab[i]);
		dprintf(2, BOLD GREEN "located at: " R "%p\n", tab[i]);
		i++;
	}
	if (tab[i] == NULL)
	{
		dprintf(2, BOLD GREEN "tab[i]: " R "%s" GREEN " ; " R, tab[i]);
		dprintf(2, BOLD GREEN "located at: " R "%p\n", tab[i]);
	}
}
