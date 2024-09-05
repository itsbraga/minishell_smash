/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   err_msg.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: art3mis <art3mis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/25 19:42:30 by annabrag          #+#    #+#             */
/*   Updated: 2024/09/05 22:05:02 by art3mis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	errmsg_no_exit(char *cmd, char *arg)
{
	if (cmd != NULL && arg == NULL)
		ft_printf(2, ERR_PREFIX, "%s: %s\n", cmd, strerror(errno));
	else if (cmd != NULL && arg != NULL)
		ft_printf(2, ERR_PREFIX, "%s: %s: %s\n", cmd, arg, strerror(errno));
	else if (cmd == NULL && arg == NULL)
		ft_printf(2, ERR_PREFIX, "%s\n", strerror(errno));
}

// change proto (cmd, arg --> in global)
// int	errmsg_cmd_exit(t_global  *g, char *cmd, char *arg, int err_status, bool cleanup)
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

int	errmsg_cmd_exit(char *cmd, char **args, int err_status)
{
	int	i;
	
	if (cmd != NULL && args == NULL)
		ft_printf(2, "%s%s: %s\n", ERR_PREFIX, cmd, strerror(errno));
	else if (cmd != NULL && args != NULL)
	{
		i = 0;
		while (args[i] != NULL)
		{
			ft_printf(2, "%s%s: %s: ", ERR_PREFIX, cmd, args[i]);
			ft_printf(2, "%s\n", strerror(errno));
			i++;
		}
	}
	return (err_status);
}

int	errmsg_exit(int reason, int err_status)
{
	if (reason == 1)
		ft_printf(2, "%s%s\n", ERR_PREFIX, ERR_NEAR_PIPE);
	else if (reason == 2)
		ft_printf(2, "%s%s\n", ERR_PREFIX, "unclosed quotes or empty quotes");
	else if (reason == 3)
		ft_printf(2, "%s%s\n", ERR_PREFIX, "failed to parse user input");
	else if (reason == 4)
		ft_printf(2, "%s%s\n", ERR_PREFIX, "failed to trim whitespaces");
	else if (reason == 5)
		ft_printf(2, "%s%s\n", ERR_PREFIX, ERR_MALLOC_LST);
	return (err_status);
}
