/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: art3mis <art3mis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 13:44:44 by pmateo            #+#    #+#             */
/*   Updated: 2024/06/24 16:27:24 by art3mis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>

typedef struct s_env
{
	char *name;
	char *value;
	struct s_env *next;
}	t_env;


int	main(int argc, char **argv, char *env)
{
	t_env *var;

	

	
}