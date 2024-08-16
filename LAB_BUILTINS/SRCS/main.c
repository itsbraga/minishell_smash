/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: annabrag <annabrag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 14:13:47 by annabrag          #+#    #+#             */
/*   Updated: 2024/08/16 14:19:42 by annabrag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	main(int argc, char **argv, char **envp)
{
	int		i;
	t_token	*tok;
	t_token	*cell;
	char **input;
	
	(void)envp;
	i = 0;
	tok = NULL;
	cell = NULL;
	if (argc != 2)
		return (EXIT_FAILURE);
	input = ft_split(argv[1], ' ');
	while (input[i])
	{
		cell = new_node(input[i]);
		if (!cell)
			return (EXIT_FAILURE);
		add_back(&tok, cell);
		i++;
	}
	display_tokens(tok);
//
	display_tokens(tok);
}
