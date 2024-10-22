/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: art3mis <art3mis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 19:44:47 by art3mis           #+#    #+#             */
/*   Updated: 2024/10/22 20:23:51 by art3mis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

static bool	__n_option_exist(char *arg)
{
	int	i;

	i = 1;
	if (arg[0] != '-' || arg[1] != 'n')
		return (false);
	while (arg[i] != '\0' && arg[i] == 'n')
		i++;
	if (arg[i] != '\0')
		return (false);
	return (true);
}
/*
	rl_on_new_line();			--> resynchronize readline
	rl_replace_line("", 0);		--> clear current line
*/
int ft_echo(t_data *d, char **args)
{
	int i;
	int flag;

	i = 1;
	flag = 0;
	while (args[i] != NULL && __n_option_exist(args[i]) == true)
	{
		flag = 1;
		i++;
	}
	while (args[i] != NULL)
	{
		ft_putstr_fd(args[i], STDOUT_FILENO);
		if (args[i + 1] != NULL)
			ft_putchar_fd(' ', STDOUT_FILENO);
		i++;
	}
	if (flag == 0)
		ft_putchar_fd('\n', STDOUT_FILENO);
	else
	{
		rl_on_new_line();		// resynchronize readline
		rl_replace_line("", 0);	// clear current line
	}
	return (d->last_exit_status = SUCCESS);
}
