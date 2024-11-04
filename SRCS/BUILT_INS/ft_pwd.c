/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: art3mis <art3mis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 14:12:03 by annabrag          #+#    #+#             */
/*   Updated: 2024/11/03 23:36:48 by art3mis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

static bool	__nothing_should_happen(const char *arg)
{
	if (arg[0] == '-' && (arg[1] == '\0' || (arg[1] == '-' && arg[2] == '\0')))
		return (true);
	else
		return (false);
}

static int	__option_error(char *arg)
{
	char	tmp[3];

	tmp[0] = arg[0];
	tmp[1] = arg[1];
	tmp[2] = '\0';
	err_msg_cmd("pwd", tmp, "invalid option", BAD_USAGE);
	ft_printf(STDERR_FILENO, "pwd: usage: pwd [no option]\n");
	return (ft_exit_status(BAD_USAGE, ADD));
}

int	ft_pwd(char **args)
{
	char	*cwd;

	if (args[1] != NULL && args[1][0] == '-')
	{
		if (__nothing_should_happen(args[1]) == false)
			return (__option_error(args[1]));
	}
	cwd = getcwd(NULL, 0);
	if (cwd == NULL)
	{
		// err_msg(NULL, ERR_PWD ERR_GETCWD ERR_BAD_FILE, 0);
		ft_printf(STDERR_FILENO, ERR_PWD ERR_GETCWD ERR_BAD_FILE "\n");
		return (ft_exit_status(FAILURE, ADD));
	}
	ft_printf(STDOUT_FILENO, "%s\n", cwd);
	free_and_set_null((void **)&cwd);
	return (ft_exit_status(SUCCESS, ADD));
}
