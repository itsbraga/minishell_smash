/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: art3mis <art3mis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 10:18:45 by art3mis           #+#    #+#             */
/*   Updated: 2024/08/22 10:28:33 by art3mis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "built_ins.h"

int	my_env(t_env *env)
{
	t_env	*tmp;

	if (env == NULL)
		return (EXIT_FAILURE);
	tmp = env;
	while (tmp != NULL)
	{
		printf("%s\n", tmp->content);
		tmp = tmp->next;
	}
	return (EXIT_SUCCESS);
}
