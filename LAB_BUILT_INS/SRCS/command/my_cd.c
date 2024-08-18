/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: art3mis <art3mis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
<<<<<<< HEAD:SRCS/PARSING/envp.c
/*   Created: 2024/08/13 15:41:26 by annabrag          #+#    #+#             */
/*   Updated: 2024/08/15 14:22:06 by art3mis          ###   ########.fr       */
=======
/*   Created: 2024/08/16 16:21:49 by annabrag          #+#    #+#             */
/*   Updated: 2024/08/16 17:51:57 by annabrag         ###   ########.fr       */
>>>>>>> 54a68bd9167e18fc7cb8e6aeea8088abc77a9926:LAB_BUILT_INS/SRCS/command/my_cd.c
/*                                                                            */
/* ************************************************************************** */

#include "built_ins.h"

static char	*home_path(char *path)
{
<<<<<<< HEAD:SRCS/PARSING/envp.c
	int		i;
	char	*path_prefix;

	i = 0;
	path_prefix = "PATH=";
	while (envp[i] != NULL)
	{
		if (ft_strncmp(envp[i], path_prefix, 5) == 0)
			return (ft_substr(envp[i], 5, ft_strlen(envp[i] - 5)));
		i++;
=======
	char	*res;

	if ((ft_strcmp(path, "~") == 0) || (ft_strcmp(path, "~/") == 0))
	{
		res = getenv("HOME");
		if (res != NULL)
		{
			res = ft_substr(path, 1, ft_strlen(path));
			return (res);
		}
>>>>>>> 54a68bd9167e18fc7cb8e6aeea8088abc77a9926:LAB_BUILT_INS/SRCS/command/my_cd.c
	}
	return (NULL);
}
