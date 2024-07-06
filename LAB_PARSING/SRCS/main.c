/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmateo <pmateo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 16:05:00 by pmateo            #+#    #+#             */
/*   Updated: 2024/07/06 16:19:07 by pmateo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../INCLUDES/mini_parsing.h"

// static void	print_token(t_token *tok)
// {
// 	while(tok != NULL)
// 	{
// 		printf("%s", tok->content);
// 		tok = tok->next;
// 		if (tok == NULL)
// 			printf("\n");
// 		else
// 			printf("->");
// 	}
// }

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
	// free_tab(input);
	display_tokens(tok);
	handle_quotes(&tok);
	display_tokens(tok);
	// expand_token(&tok, envp);
}