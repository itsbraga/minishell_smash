/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   err_msg.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: annabrag <annabrag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/25 19:42:30 by annabrag          #+#    #+#             */
/*   Updated: 2024/08/29 20:40:02 by annabrag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "my_builtins.h"

void	errmsg(char *cmd, char *arg)
{
	if (cmd != NULL && arg == NULL)
	{
		printf("%s %s: ", ERR_PREFIX, cmd);
		printf("%s\n", strerror(errno));
	}
	else if (cmd != NULL && arg != NULL)
	{
		printf("%s %s: %s: ", ERR_PREFIX, cmd, arg);
		printf("%s\n", strerror(errno));
	}
	else if (cmd == NULL && arg == NULL)
		printf("%s %s\n", ERR_PREFIX, strerror(errno));
}

// change proto (cmd, arg --> in global)
// int	errmsg_exit_status(t_global  *g, char *cmd, char *arg, int err_status, bool cleanup)
// {
// 	if (cmd != NULL && arg == NULL)
// 	{
// 		printf("%s %s: ", ERR_PREFIX, cmd);
// 		printf("%s\n", strerror(errno));
// 	}
// 	else if (cmd != NULL && arg != NULL)
// 	{
// 		printf("%s %s: %s: ", ERR_PREFIX, cmd, arg);
// 		printf("%s\n", strerror(errno));
// 	}
// 	if (cleanup == true)
// 		clean_exit_shell(g, err_status);
// 	return (err_status);
// }

int	errmsg_exit_status(char *cmd, char *arg, int err_status)
{
	if (cmd != NULL && arg == NULL)
	{
		printf("%s %s: ", ERR_PREFIX, cmd);
		printf("%s\n", strerror(errno));
	}
	else if (cmd != NULL && arg != NULL)
	{
		printf("%s %s: %s: ", ERR_PREFIX, cmd, arg);
		printf("%s\n", strerror(errno));
	}
	return (err_status);
}
