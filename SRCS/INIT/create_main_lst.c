/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_main_lst.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: annabrag <annabrag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 16:02:17 by annabrag          #+#    #+#             */
/*   Updated: 2024/09/02 20:17:37 by annabrag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*  1-  Les espaces dans les quotes (' et ")
*/
int	create_main_lst(t_global *g, char *user_input)
{
	t_main_lst	*new_node;
    char        **tokens;
    size_t      i;

	if (user_input == NULL)
		return (FAILURE);
    tokens = ft_split(user_input, '|');
    if (tokens == NULL)
        return (FAILURE);
    i = 0;
	while (tokens[i] != NULL)
	{
        new_node = main_new_node(tokens[i]);
		if (new_node == NULL)
            return (perror("Failed to allocate memory"), free_tab(tokens), 1);
		main_add_back(&g->main, new_node);
        i++;
	}
    free_tab(tokens);
	return (SUCCESS);
}
