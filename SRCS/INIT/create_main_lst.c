/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_main_lst.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: art3mis <art3mis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 16:02:17 by annabrag          #+#    #+#             */
/*   Updated: 2024/09/04 02:00:57 by art3mis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*  1-  Les espaces dans les quotes (' et ") ne doivent pas etre supprimés
	2-  ?
*/

// int	check_closed_quotes(char *user_input)
// {
// 	bool	closed_quotes[2] = {true, true};
// 	int		i;

//     while (user_input[i] != '\0')
//     {
// 		if (user_input[i] == '\'')
// 			closed_quotes[0] = switch_bool(closed_quotes[0]);
// 		else if (user_input[i] == '"')
// 			closed_quotes[1] = switch_bool(closed_quotes[1]);
// 		i++;
//     }
//     if (closed_quotes[0] == false || closed_quotes[1] == false)
//     {
// 		perror("Unmatched quotes in your input");
// 		return (FAILURE);
//     }
//     return (SUCCESS);
// }
char	**parse_input_with_quotes(char *str)
{
	char	**tokens;
	int		i;
	int		start;
	int		token_count;
	bool	closed_quotes[2] = {true, true};

	tokens = malloc(sizeof(char *) * ft_strlen(str) + 1);
	if (tokens == NULL)
		return (NULL);
	i = 0;
	while (str[i] != '\0')
	{
		while (ft_isspace(str[i]) == 1)
			i++;
		if (str[i] == '\0')
			break ;
		start = i;
		while (str[i] != '\0' && (str[i] != '|' || closed_quotes[0] == false
			|| closed_quotes[1] == false))
		{
			if (str[i] == '\'')
				closed_quotes[0] = switch_bool(closed_quotes[0]);
			else if (str[i] == '"')
				closed_quotes[1] = switch_bool(closed_quotes[1]);
			i++;
		}
		tokens[token_count++] = ft_strldup(str + start, i - start);
		if (str[i] == '|')
			i++;
	}
	tokens[token_count] = NULL;
	return (tokens);
}

// int	create_main_lst(t_global *g, char *user_input)
// {
// 	t_main_lst	*new_node;
// 	char		**tokens;
// 	size_t      i;

// 	if (user_input == NULL)
// 		return (FAILURE);
// 	lstclear_main(&g->main);
// 	if ((ft_strchr(user_input, '"') != NULL) || (ft_strchr(user_input, '\'') != NULL))
// 		tokens = parse_input_with_quotes(user_input);
// 	else
// 		tokens = ft_split(user_input, '|');
// 	if (tokens == NULL)
// 		return (FAILURE);
// 	i = 0;
// 	while (tokens[i] != NULL)
// 	{
// 		new_node = main_new_node(tokens[i]);
// 		if (new_node == NULL)
// 		{
// 			perror("Failed to allocate memory for a new node");
// 			free_tab(tokens);
// 			return (FAILURE);
// 		}
// 		main_add_back(&g->main, new_node);
// 		i++;
// 	}
// 	free_tab(tokens);
// 	return (SUCCESS);
// }

// gerer le cas ou apres le pipe il n'y a rien >> n'est pas cense creer un node vide
int	create_main_lst(t_global *g, char *user_input)
{
	t_main_lst	*new_node;
	char        **tokens;
	size_t      i;

	if (user_input == NULL)
		return (FAILURE);
	lstclear_main(&g->main);
	tokens = ft_split(user_input, '|');
	if (tokens == NULL)
		return (FAILURE);
	i = 0;
	while (tokens[i] != NULL)
	{
		// if (ft_strcmp(tokens[i], "|") == 0 && tokens[i + 1] == NULL)
		// 	break ;
		new_node = main_new_node(tokens[i]);
		if (new_node == NULL)
		{
			perror("Failed to allocate memory for a new node");
			free_tab(tokens);
			return (FAILURE);
		}
		main_add_back(&g->main, new_node);
		i++;
	}
	free_tab(tokens);
	return (SUCCESS);
}

int del_unwanted_char(t_main_lst *main)
{
	t_main_lst  *head;
	char        *trimmed_token;
	size_t		len;

	head = main;
	len = ft_strlen(head->content);
	while (head != NULL)
	{
		if (((head->content[0] == '"') && (head->content[len - 1] == '"'))
			|| ((head->content[1] == '\'') && (head->content[len - 1] == '\'')))
		{
			head = head->next;
			continue ;
		}
		trimmed_token = ft_strtrim(head->content, " ");
		if (trimmed_token == NULL)
		{
			perror("Failed to trim whitespaces from token");
			return (FAILURE);
		}
		free(head->content);
		head->content = trimmed_token;
		head = head->next;
	}
	return (SUCCESS);
}
