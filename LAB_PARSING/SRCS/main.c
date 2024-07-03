/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmateo <pmateo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 16:05:00 by pmateo            #+#    #+#             */
/*   Updated: 2024/07/03 18:22:01 by pmateo           ###   ########.fr       */
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

void    expand_token(t_token *t, t_token *current)
{
	int     i;
	char    *match;
	char    *to_find;

	i = 0;
	match = NULL;
	
	
	
}
// Le flag "to_expand" ne doit etre mis a 1 selon deux facteurs, si le parser a rencontre un $
// en debut de string, et 
// void    handle_expansion(t_token *t)
// {
// 	t_token *current;
	
// 	current = g->token;
// 	while (current->content)
// 	{
// 		if (current->to_expand)
// 		{
// 			if (current->t_quoted != D_QUOTE_INSIDE)
// 				expand_token(g, current);  
// 		}
// 		else
// 			current = current->next;
// 	}    
// }

void	assign_token(t_token *current)
{
	if (is_only_single_quote(current) == 1)
		current->quote_way = ONLY_SQUOTE;
	else if (is_only_double_quote(current == 1))
		current->quote_way = ONLY_DQUOTE; 
	if (current->quote_way = NULL)
		
		
}

void	expand_token(t_token **tok, char **envp)
{
	t_token *current;

	current = *tok;
	while (current->next != NULL)
	{
		assign_token(current);
		current = current->next;
	}
}

// Si '' ou "" il me faut supprimer les quotes
// Si single quote avec au moins un charactere a l'interieur = literal value except ENVVAR
// Si double quote avec au moins un charactere a l'interieur = literal value 

int	main(int argc, char **argv, char **envp)
{
	t_token	*tok;
	t_token	*cell;
	char **input;
	
	tok = NULL;
	cell = NULL;
	if (argc != 2)
		return (EXIT_FAILURE);
	input = ft_split(argv[1], ' ');
	while (*input)
	{
		cell = new_node(*input);
		if (!cell)
			return (EXIT_FAILURE);
		add_back(&tok, cell);
		input++;	
	}
	free_tab(input);
	expand_token(&tok, envp);
	
	
	
}