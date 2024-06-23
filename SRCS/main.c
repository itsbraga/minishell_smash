/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmateo <pmateo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 21:02:12 by pmateo            #+#    #+#             */
/*   Updated: 2024/04/24 14:38:49 by pmateo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../INCLUDES/minishell.h"

int main(int argc, char **argv, char **envp)
{
    t_global global;
    
    if (argc > 1)
        exit(EXIT_FAILURE);
    (void)argv;
    init_global(&global);
	global.envp = envp;
    while (1)
    {
        ft_printf("@_@ $> ");
        global.input = get_next_line(0);
		if (global.input)
			add_history(global.input);
		
    }
    return (0);
}