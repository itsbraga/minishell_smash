/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: art3mis <art3mis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 19:44:47 by art3mis           #+#    #+#             */
/*   Updated: 2024/10/07 21:57:06 by art3mis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "my_builtins.h"

int my_echo(char **args)
{
    int i;

    i = 0;
    while (args[i] != NULL)
    {
        ft_printf(STDOUT_FILENO, "%s", args[i]);
        if (args[i] != NULL)
            ft_printf(STDOUT_FILENO, ' ');
        i++;
    }
}