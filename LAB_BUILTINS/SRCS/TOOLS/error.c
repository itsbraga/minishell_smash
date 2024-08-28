/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: annabrag <annabrag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/25 19:42:30 by annabrag          #+#    #+#             */
/*   Updated: 2024/08/28 17:12:07 by annabrag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "my_builtins.h"

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

int	errmsg_status_exit(char *cmd, char *arg, int err_status)
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
