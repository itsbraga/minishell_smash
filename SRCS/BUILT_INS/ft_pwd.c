/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: annabrag <annabrag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 14:12:03 by annabrag          #+#    #+#             */
/*   Updated: 2024/10/23 18:53:41 by annabrag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int	ft_pwd(void)
{
	char	cwd[PATH_MAX];
	t_data	*d;

	if (getcwd(cwd, sizeof(cwd)) == NULL)
	{
		err_msg("0: getcwd() failed", ERR_BAD_FILE, 0);
		return (errno);
	}
	ft_printf(STDOUT_FILENO, "%s\n", cwd);
	d = data_struct();
	d->last_exit_status = SUCCESS;
	return (d->last_exit_status);
}
