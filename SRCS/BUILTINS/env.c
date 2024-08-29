/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: annabrag <annabrag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 10:18:45 by art3mis           #+#    #+#             */
/*   Updated: 2024/08/29 20:39:04 by annabrag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	my_env(t_env *env)
{
	t_env	*tmp;

	if (env == NULL)
	{
		printf("%s %s\n", ERR_PREFIX, "environment deleted.");
		return (FAILURE);
	}
	tmp = env;
	while (tmp != NULL)
	{
		printf("%s\n", tmp->content);
		tmp = tmp->next;
	}
	return (SUCCESS);
}
