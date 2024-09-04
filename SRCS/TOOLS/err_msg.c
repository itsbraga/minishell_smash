/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   err_msg.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: annabrag <annabrag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/25 19:42:30 by annabrag          #+#    #+#             */
/*   Updated: 2024/09/04 20:00:06 by annabrag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	errmsg_no_exit(char *cmd, char *arg)
{
	if (cmd != NULL && arg == NULL)
		ft_printf(STDERR_FILENO, ERR_PREFIX, "%s: %s\n", cmd, strerror(errno));
	else if (cmd != NULL && arg != NULL)
	{
		ft_printf(STDERR_FILENO, ERR_PREFIX, "%s: %s: ", cmd, arg);
		ft_printf(STDERR_FILENO, "%s\n", strerror(errno));
	}
	else if (cmd == NULL && arg == NULL)
		ft_printf(STDERR_FILENO, ERR_PREFIX, "%s\n", strerror(errno));
}

// change proto (cmd, arg --> in global)
// int	errmsg_exit(t_global  *g, char *cmd, char *arg, int err_status, bool cleanup)
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

int	errmsg_exit(char *cmd, char **args, int err_status)
{
	int	i;
	
	if (cmd != NULL && args == NULL)
		ft_printf(STDERR_FILENO, ERR_PREFIX, "%s: %s\n", cmd, strerror(errno));
	else if (cmd != NULL && args != NULL)
	{
		i = 0;
		while (args[i] != NULL)
		{
			ft_printf(STDERR_FILENO, ERR_PREFIX, "%s: %s: ", cmd, args[i]);
			ft_printf(STDERR_FILENO, "%s\n", strerror(errno));
			i++;
		}
	}
	return (err_status);
}

int	errmsg_std(int reason, char *arg, int err_status)
{
	if (reason == 1)
	{
		ft_printf(STDERR_FILENO, ERR_PREFIX);
		ft_printf(STDERR_FILENO, "syntax error near unexpected token ");
		ft_printf(STDERR_FILENO, "`%s'\n", arg);
	}
	// else if (reason == 2)
	// {
	// 	ft_printf(STDERR_FILENO, "%s ", ERR_PREFIX);
	// 	perror("error near unexpected token");
	// 	ft_printf(STDERR_FILENO, " `%c'", &arg);
	// }
	return (err_status);
}
