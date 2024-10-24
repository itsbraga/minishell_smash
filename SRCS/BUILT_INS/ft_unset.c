/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: annabrag <annabrag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 18:38:48 by annabrag          #+#    #+#             */
/*   Updated: 2024/10/24 21:11:17 by annabrag         ###   ########.fr       */
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
	return (ft_exit_status(SUCCESS, ADD));
}
