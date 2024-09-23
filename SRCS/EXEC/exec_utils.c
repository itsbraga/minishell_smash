/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmateo <pmateo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 13:24:08 by pmateo            #+#    #+#             */
/*   Updated: 2024/09/23 19:58:18 by pmateo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

char	*search_bin(char *cmd, char **tab_path)
{
	
}

char	*search_path(char **tab_path, char **env)
{
	char	*all_path;
	int		i;

	all_path = NULL;
	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], "PATH", 4) != 0)
			i++;
		else
		{
			all_path = env[i];
			break;
		}
	}
	if (all_path)
	{
		tab_path = ft_split(all_path, ':');
		if (!tab_path)
		{
			perror("malloc");
			clean_exit_shell(1);
		}
	}
	return (tab_path);
}

void	check_bin_path()
{
	
}