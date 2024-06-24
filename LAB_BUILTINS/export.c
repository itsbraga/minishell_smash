/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmateo <pmateo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 13:44:44 by pmateo            #+#    #+#             */
/*   Updated: 2024/06/09 16:20:48 by pmateo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>

typedef struct s_envlist
{
	char *name;
	char *value;
	struct s_envlist *next;
}	t_envlist;


int	main(int argc, char **argv, char *env)
{
	t_envlist *var;

	

	
}