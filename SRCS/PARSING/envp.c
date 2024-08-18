/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: art3mis <art3mis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 15:41:26 by annabrag          #+#    #+#             */
/*   Updated: 2024/08/15 14:22:06 by art3mis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// add a path:	PATH=$PATH:~/opt/bin
//			or	PATH=~/opt/bin:$PATH	

char	*find_path(char **envp)
{
	int		i;
	char	*path_prefix;

	i = 0;
	path_prefix = "PATH=";
	while (envp[i] != NULL)
	{
		if (ft_strncmp(envp[i], path_prefix, 5) == 0)
			return (ft_substr(envp[i], 5, ft_strlen(envp[i] - 5)));
		i++;
	}
	return (NULL);
}
