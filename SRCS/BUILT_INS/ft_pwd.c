/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: annabrag <annabrag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 14:12:03 by annabrag          #+#    #+#             */
/*   Updated: 2024/11/02 19:35:14 by annabrag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

static int	__option_error(char **args)
{
	char	tmp[3];

	tmp[0] = args[1][0];
	tmp[1] = args[1][1];
	tmp[2] = '\0';
	err_msg_cmd("pwd", tmp, "invalid option", BAD_USAGE);
	ft_printf(STDERR_FILENO, "pwd: usage: pwd [no option]\n");
	return (ft_exit_status(BAD_USAGE, ADD));
}

int	ft_pwd(char **args)
{
	char	*cwd;

	if (args[1] != NULL)
		return (__option_error(args));
	cwd = getcwd(NULL, 0);
	if (cwd == NULL)
	{
		err_msg(NULL, ERR_PWD ERR_GETCWD ERR_BAD_FILE, 0);
		return (ft_exit_status(FAILURE, ADD));
	}
	ft_printf(STDOUT_FILENO, "%s\n", cwd);
	free_and_set_null((void **)&cwd);
	return (ft_exit_status(SUCCESS, ADD));
}
