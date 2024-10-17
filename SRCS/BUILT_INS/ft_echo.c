/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: annabrag <annabrag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 19:44:47 by art3mis           #+#    #+#             */
/*   Updated: 2024/10/17 15:40:27 by annabrag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

int ft_echo(char **args)
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
		rl_on_new_line();		// resyncrhonize readline
		rl_replace_line("", 0);	// clear current line
	}
	return (SUCCESS);
}
