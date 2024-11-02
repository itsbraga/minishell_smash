/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: annabrag <annabrag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 20:27:06 by pmateo            #+#    #+#             */
/*   Updated: 2024/11/02 21:10:07 by annabrag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void	close_hd_all_nodes(t_data *d)
{
	t_exec_lst	*curr;

	curr = d->exec;
	while (curr != NULL)
	{
		if (curr->latest_hd != 0)
			close(curr->latest_hd);
		curr = curr->next;
	}
}

void	close_hd_other_nodes(t_data *d, t_exec_lst *node)
{
	t_exec_lst	*curr;

	curr = d->exec;
	while (curr != node)
		curr = curr->next;
	curr = curr->next;
	while (curr != NULL)
	{
		if (curr->latest_hd != 0)
			close(curr->latest_hd);
		curr = curr->next;
	}
}

bool	check_if_is_dir(char *bin_path)
{
	struct stat	s_bin_path;

	if (stat(bin_path, &s_bin_path) == 0)
	{
		if (S_ISDIR(s_bin_path.st_mode) != 0)
			return (true);
	}
	return (false);
}

char	**search_path(char **tab_path, char **env)
{
	char	*all_path;
	int		i;

	all_path = NULL;
	i = 0;
	while (env[i] != NULL)
	{
		if (ft_strncmp(env[i], "PATH", 4) != 0)
			i++;
		else
		{
			all_path = env[i];
			break ;
		}
	}
	if (all_path != NULL)
	{
		tab_path = yama(ADD_TAB, ft_split(all_path, ':'), 0);
		secure_malloc(tab_path, true);
	}
	return (tab_path);
}
