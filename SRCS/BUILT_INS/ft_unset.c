/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: art3mis <art3mis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 18:38:48 by annabrag          #+#    #+#             */
/*   Updated: 2024/10/22 20:24:20 by art3mis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int	ft_unset(t_data *d, char **args)
{
	int		i;

	i = 1;
	while (args[i] != NULL)
	{
		del_env_var(&(d->env), args[i]);
		del_env_var(&(d->exp_env), args[i]);
		i++;
	}
	return (d->last_exit_status = SUCCESS);
}
