/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: art3mis <art3mis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 14:12:03 by annabrag          #+#    #+#             */
/*   Updated: 2024/08/22 10:26:20 by art3mis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "built_ins.h"

/*	PWD means Print Working Directory	
	The $PWD environment variable is a dynamic variable
	that stores the path to the current working directory.
*/

int	my_pwd(void)
{
	char	cwd[PATH_MAX];

	if (getcwd(cwd, sizeof(cwd)) == NULL)
	{
		printf("%s%s", BOLD RED "minishell: ", RESET "getcwd: ");
		printf("%s\n", strerror(errno));
		return (EXIT_FAILURE);
	}
	printf("%s\n", cwd);
	return (EXIT_SUCCESS);
}
