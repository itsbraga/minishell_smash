/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   err_msg.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: annabrag <annabrag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/25 19:42:30 by annabrag          #+#    #+#             */
/*   Updated: 2024/09/02 15:36:25 by annabrag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	errmsg(char *cmd, char *arg)
{
	if (cmd != NULL && arg == NULL)
		printf("%s %s: %s\n", ERR_PREFIX, cmd, strerror(errno));
	else if (cmd != NULL && arg != NULL)
		printf("%s %s: %s: %s\n", ERR_PREFIX, cmd, arg, strerror(errno));
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

int	errmsg_exit_status(char *cmd, char **args, int err_status)
{
	int	i;
	
	if (cmd != NULL && args == NULL)
		printf("%s %s: %s\n", ERR_PREFIX, cmd, strerror(errno));
	else if (cmd != NULL && args != NULL)
	{
		i = 0;
		while (args[i] != NULL)
		{
			printf("%s %s: %s: ", ERR_PREFIX, cmd, args[i]);
			printf("%s\n", strerror(errno));
			i++;
		}
	}
	return (err_status);
}
