/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: annabrag <annabrag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 14:12:03 by annabrag          #+#    #+#             */
/*   Updated: 2024/08/28 17:12:07 by annabrag         ###   ########.fr       */
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
		errmsg_status_exit("getcwd", NULL, errno); //  a verifier si errno
	printf("%s\n", cwd);
	return (SUCCESS);
}
