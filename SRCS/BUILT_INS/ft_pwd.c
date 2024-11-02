/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: art3mis <art3mis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 14:12:03 by annabrag          #+#    #+#             */
/*   Updated: 2024/11/02 00:27:41 by art3mis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int	ft_pwd(void)
{
	char	*cwd;

	cwd = getcwd(NULL, 0);
	if (cwd == NULL)
	{
		err_msg(NULL, ERR_PWD ERR_GETCWD ERR_BAD_FILE, 0);
		return (ft_exit_status(FAILURE, ADD));
	}
	ft_printf(STDOUT_FILENO, "%s\n", cwd);
	// free_and_set_null(cwd);
	free_and_set_null((void **)&cwd);
	return (ft_exit_status(SUCCESS, ADD));
}
