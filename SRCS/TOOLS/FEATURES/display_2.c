/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmateo <pmateo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 20:56:55 by annabrag          #+#    #+#             */
/*   Updated: 2024/10/23 16:23:38 by pmateo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tools.h"

void	display_exec_lst(t_exec_lst **e)
{
	t_exec_lst	*current;

	current = *e;
	ft_printf(1, R BOLD Y LIM " t_exec_lst " LIM "\n" R);
	while (current != NULL)
	{
		ft_printf(1, "--- NODE ---\n");
		ft_printf(1, Y "heredoc_nb:\t [" R "%d" Y "]\n" R, current->heredoc_nb);
		ft_printf(1, Y "absolute_path:\t [" R);
		ft_printf(1, "%d" Y "]\n" R, current->absolute_path);
		ft_printf(1, Y "bin_path:\t [" R "%s" Y "]\n" R, current->bin_path);
		if (current->cmd != NULL)
			print_cmd(current->cmd);
		else
			ft_printf(1, Y "cmd:\t\t [" R "(null)" Y "]\n" R);
		if (current->redir != NULL)
			display_redir_lst(&(current->redir));
		else
			ft_printf(1, BOLD Y "t_redir_lst:\t [" R "(null)" BOLD Y "]\n" R);
		current = current->next;
	}
	if (current == NULL)
		ft_putendl_fd("", 1);
}

void	print_cmd(char **cmd)
{
	int	i;

	i = 0;
	while (cmd[i] != NULL)
	{
		dprintf(2, Y "cmd[i]:\t\t [" R "%s" Y "]\t @bloc " R, cmd[i]);
		dprintf(2, "%p\n", cmd[i]);
		i++;
	}
}

void	print_tab2(char **tab)
{
	int i;

	i = 0;
	if (tab)
		dprintf(2, "tab existe\n");
	else
		dprintf(2, "tab n'existe pas\n");
	if (tab[i])
	{
		while (tab[i])
		{
			dprintf(2, "tab[%d] = %s\n", i, tab[i]);
			i++;
		}
	}
	else
		dprintf(2, "tab existe mais est vide\n");

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

void	display_shell_info(void)
{
	ft_printf(STDOUT_FILENO, "\rPID : %d\n", getpid());
	if (isatty(STDIN_FILENO) == 1)
		printf("STDIN connected to terminal :)\n");
	else
		printf("STDIN isn't connected to terminal /!\\\n");
}
