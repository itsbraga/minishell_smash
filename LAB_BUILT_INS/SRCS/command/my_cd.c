/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: annabrag <annabrag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 16:21:49 by annabrag          #+#    #+#             */
/*   Updated: 2024/08/16 17:51:57 by annabrag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "built_ins.h"

static char	*home_path(char *path)
{
	char	*res;

	if ((ft_strcmp(path, "~") == 0) || (ft_strcmp(path, "~/") == 0))
	{
		res = getenv("HOME");
		if (res != NULL)
		{
			res = ft_substr(path, 1, ft_strlen(path));
			return (res);
		}
	}
}