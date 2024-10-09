/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: annabrag <annabrag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 20:56:55 by annabrag          #+#    #+#             */
/*   Updated: 2024/10/09 22:29:30 by annabrag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	display_exec_lst(t_exec_lst *e)
{
	t_exec_lst	*tmp;

	tmp = e;
	while (tmp != NULL)
	{
		// display_redir_lst(tmp->redir);
		ft_printf(STDOUT_FILENO, R BOLD YELLOW "[t_exec_lst]\n" R);
		ft_printf(2, YELLOW "heredoc_nb:\t [" R "%d" YELLOW "]\n" R, tmp->heredoc_nb);
		ft_printf(2, YELLOW "absolute_path:\t [" R "%d" YELLOW "]\n" R, tmp->absolute_path);
		ft_printf(2, YELLOW "bin_path:\t [" R "%s" YELLOW "]\n" R, tmp->bin_path);
		print_tab(tmp->cmd);
		tmp = tmp->next;
	}
}

void	print_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i] != NULL)
	{
		dprintf(2, BOLD GREEN "tab[i] = %s\t| ptr of tab[i] = %p\n" R, tab[i], tab[i]);
		i++;
	}
	if (tab[i] == NULL)
		dprintf(2, BOLD GREEN "tab[i] = %s | ptr of tab[i] = %p\n" R, tab[i], tab[i]);
}
