/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: art3mis <art3mis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 16:05:00 by pmateo            #+#    #+#             */
/*   Updated: 2024/08/18 22:37:41 by art3mis          ###   ########.fr       */
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
		printf("%s\n", input);
		input = handle_quotes_and_expand(input, envp);
		printf("%s\n", input);
		// free(input);
	}
	return (0);
}

//NOTES : 
// - artefact avec "'$USER'" lors de la premiere commande
// - """'pmateo'" pars en cacahouette (soucis avec empty quote)
// - Variable inexistante non supprime, revoir les conditions d'acces a expand