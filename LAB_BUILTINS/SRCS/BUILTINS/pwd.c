/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: art3mis <art3mis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 14:12:03 by annabrag          #+#    #+#             */
/*   Updated: 2024/09/05 21:43:48 by art3mis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "my_builtins.h"

/*	PWD means Print Working Directory	
	The $PWD environment variable is a dynamic variable
	that stores the path to the current working directory.
*/
int	my_pwd(void)
{
	char	cwd[PATH_MAX];

	if (getcwd(cwd, sizeof(cwd)) == NULL)
		return (errmsg_cmd_exit("getcwd", NULL, errno));
	printf("%s\n", cwd);
	// g->last_exit_status = 0;
	return (SUCCESS);
}
