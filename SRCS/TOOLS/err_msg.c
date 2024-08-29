/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   err_msg.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: annabrag <annabrag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/25 19:42:30 by annabrag          #+#    #+#             */
/*   Updated: 2024/08/29 18:29:23 by annabrag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	errmsg(char *cmd, char *arg)
{
	if (cmd != NULL && arg == NULL)
	{
		printf("%s %s: ", BOLD RED "minishell:" RESET, cmd);
		printf("%s\n", strerror(errno));
	}
	else if (cmd != NULL && arg != NULL)
	{
		printf("%s %s: %s: ", BOLD RED "minishell:" RESET, cmd, arg);
		printf("%s\n", strerror(errno));
	}
	else if (cmd == NULL && arg == NULL)
		printf("%s %s\n", BOLD RED "minishell:" RESET, strerror(errno));
}

// change proto (cmd, arg --> in global)
// int	errmsg_exit_status(t_global  *g, char *cmd, char *arg, int err_status, bool cleanup)
// {
// 	if (cmd != NULL && arg == NULL)
// 	{
// 		printf("%s %s: ", BOLD RED "minishell:" RESET, cmd);
// 		printf("%s\n", strerror(errno));
// 	}
// 	else if (cmd != NULL && arg != NULL)
// 	{
// 		printf("%s %s: %s: ", BOLD RED "minishell:" RESET, cmd, arg);
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
		printf("%s %s: ", BOLD RED "minishell:" RESET, cmd);
		printf("%s\n", strerror(errno));
	}
	else if (cmd != NULL && arg != NULL)
	{
		printf("%s %s: %s: ", BOLD RED "minishell:" RESET, cmd, arg);
		printf("%s\n", strerror(errno));
	}
	return (err_status);
}
