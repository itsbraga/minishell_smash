/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: annabrag <annabrag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 16:05:00 by pmateo            #+#    #+#             */
/*   Updated: 2024/08/19 20:17:52 by annabrag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*   Updated: 2024/08/19 19:42:35 by pmateo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../INCLUDES/mini_parsing.h"

void	free_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

// int	main(int argc, char **argv, char **envp)
// {
// 	int		i;
// 	t_token	*tok;
// 	t_token	*cell;
// 	char **input;
	
// 	i = 0;
// 	tok = NULL;
// 	cell = NULL;
// 	if (argc != 2)
// 		return (EXIT_FAILURE);
// 	input = ft_split(argv[1], ' ');
// 	while (input[i])
// 	{
// 		cell = new_node(input[i]);
// 		if (!cell)
// 			return (EXIT_FAILURE);
// 		add_back(&tok, cell);
// 		i++;
// 	}
// 	// free_tab(input);
// 	display_tokens(tok);
// 	handle_quotes_and_expand(&tok, envp);
// 	display_tokens(tok);
// }

int	main(int argc, char **argv, char **envp)
{
	char *input;
	
	if (argc > 1)
		exit(EXIT_FAILURE);
	(void)argv;
	while (1)
	{
		input = readline("minishell> ");
		printf("before : %s\n", input);
		input = handle_quotes_and_expand(input, envp);
		printf("after :%s\n", input);
		free(input);
	}
	return (0);
}

//PROBLEMES : 
// - Soucis sur empty quotes : """'''"""''$USER''"""'''"""
