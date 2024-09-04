/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_main_lst.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: annabrag <annabrag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 16:02:17 by annabrag          #+#    #+#             */
/*   Updated: 2024/09/04 20:02:26 by annabrag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	quote_parser(t_parser *p)
{
	p->closed_quotes[0] = true;
	p->closed_quotes[1] = true;
	while (ft_isspace(p->user_input[p->i]) == 1)
			p->i += 1;
	if (p->user_input[p->i] == '\0')
		return (FAILURE);
	else if (p->user_input[p->i] == '|')
		return (errmsg_std(1, &p->user_input[p->i], FAILURE));
	p->start = p->i;
	while (p->user_input[p->i] != '\0' && (p->user_input[p->i] != '|'
			|| p->closed_quotes[0] == false || p->closed_quotes[1] == false))
	{
		if (p->user_input[p->i] == '\'')
			p->closed_quotes[0] = switch_bool(p->closed_quotes[0]);
		else if (p->user_input[p->i] == '"')
			p->closed_quotes[1] = switch_bool(p->closed_quotes[1]);
		p->i += 1;
	}
	p->tokens[p->token_count++] = ft_strldup(p->user_input + p->start, p->i - p->start);
	if (p->user_input[p->i] == '|')
		p->i += 1;
	return (SUCCESS);
}

char	**parse_user_input(char *input)
{
	t_parser	p;

	ft_bzero(&p, sizeof(p));
	p.user_input = input;
	if (p.user_input == NULL || p.user_input[0] == '\0')
		return (NULL);
	if (ft_strchr(input, '"') != NULL || ft_strchr(input, '\'') != NULL)
	{
		p.tokens = malloc(sizeof(char *) * (ft_strlen(p.user_input) + 1));
		if (p.tokens == NULL)
			return (NULL);
		while (p.user_input[p.i] != '\0')
		{
			if (quote_parser(&p) == FAILURE)
				return (NULL);
		}
		p.tokens[p.token_count] = NULL;
	}
	else
		p.tokens = ft_split(input, '|');
	return (p.tokens);
}

int	create_main_lst(t_global *g, char *input)
{
	t_main_lst	*new_node;
	char		**tokens;
	size_t      i;

	lstclear_main(&g->main);
	tokens = parse_user_input(input);
	if (tokens == NULL)
		return (FAILURE);
	i = 0;
	while (tokens[i] != NULL)
	{
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
