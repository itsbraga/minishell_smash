/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: annabrag <annabrag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 15:41:26 by annabrag          #+#    #+#             */
/*   Updated: 2024/08/13 15:48:38 by annabrag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// add a path:	PATH=$PATH:~/opt/bin
//			or	PATH=~/opt/bin:$PATH	

char	*find_path(char **envp)
{
	int	i;

	i = 0;
	while (envp[i] != '\0')
	{
		if (!strncmp(envp, "PATH=", 5))
			return (ft_substr(envp[i], 5, ft_strlen(envp[i] - 5)));
	}
}