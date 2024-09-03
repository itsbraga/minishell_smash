/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmateo <pmateo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 19:38:19 by pmateo            #+#    #+#             */
/*   Updated: 2024/09/03 16:42:07 by pmateo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../INCLUDES/mini_exec.h"

void	display_tokens(t_tok *t)
{
	t_tok	*tmp;

	tmp = t;
	while (tmp != NULL)
	{
		ft_putstr_fd(tmp->content, 1);
		ft_putendl_fd("", 1);
		tmp = tmp->next;
	}
}
//TOUT LES CHAR * AUTRE QUE CONTENT SONT DE SIMPLES POINTEURS SUR LES ELEMENTS EN QUESTION
//SI LE POINTEUR EST A NUL C'EST QUE L'ELEMENT N'EST PAS PRESENT, SINON CELA POINTE SUR LE PREMIERE CHAR DE L'ELEMENT
static t_tok	*new_node(char *content)
{
	t_tok	*new_node;
	
	new_node = malloc(sizeof(t_tok));
	if (!new_node)
		return (NULL);
	new_node->content = ft_strdup(content);
	new_node->here_doc = NULL;
	new_node->limiter = NULL;
	new_node->append = NULL;
	new_node->red_in = NULL;
	new_node->infile = NULL;
	new_node->red_out = NULL;
	new_node->outfile = NULL;
	new_node->next = NULL;
	return (new_node);
}

static t_tok	*last_node(t_tok *t)
{
	if (!t)
		return (NULL);
	while (t->next != NULL)
		t = t->next;
	return (t);
}

static void	add_back(t_tok **t, t_tok *new_node)
{
	t_tok	*tmp;

	if (!(*t))
		*t = new_node;
	else
	{
		tmp = last_node(*t);
		tmp->next = new_node;
	}
}

void	build_lst(char *input, t_tok **cmd)
{
	t_tok	*node;
	char	*extracted;
	char *start = NULL;
	char *end = NULL;
	
	node = NULL;
	extracted = NULL;
	while (*input != '\0')
	{
		start = ft_strchr(input, '"') + 1;
		end = ft_strchr(start + 1, '"');
		size_t length = end - start;
		extracted = ft_strldup(start, length);
		node = new_node(extracted);
		add_back(cmd, node);
		input = end + 1;
		free(extracted);
	}
}