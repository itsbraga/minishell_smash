/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmateo <pmateo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 19:38:19 by pmateo            #+#    #+#             */
/*   Updated: 2024/09/19 19:14:21 by pmateo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../INCLUDES/mini_exec.h"

size_t	get_lst_size(t_exec_lst *e_lst)
{
	size_t	size;
	t_exec_lst *node;

	size = 0;
	if (e_lst)
		node = e_lst;
	while (node != NULL)
	{
		size++;
		node = node->next;
	}
	return (size);
	
}

void	display_tokens(t_exec_lst *t)
{
	t_exec_lst	*tmp;

	tmp = t;
	while (tmp != NULL)
	{
		ft_putendl_fd(tmp->content, 1);
		tmp = tmp->next;
	}
}

void	display_tokens_with_infos(t_exec_lst *t)
{
	t_exec_lst	*tmp;
	int	i;
	int	j;

	tmp = t;
	i = 0;
	j = 0;
	while (tmp != NULL)
	{
		printf("###### %d ######\n", i++);
		if(tmp->here_doc)
		{
			printf("HERE_DOC = %s\n", tmp->here_doc);
			printf("LIMITER = %s|\n", tmp->limiter);
		}
		if (tmp->append)
		{
			printf("APPEND = %s\n", tmp->append);
			printf("OUTFILE = %s|\n", tmp->outfile);
		}
		if (tmp->red_in)
		{
			printf("RED_IN = %s\n", tmp->red_in);
			printf("INFILE = %s|\n", tmp->infile);
		}
		if (tmp->red_out)
		{
			printf("RED_OUT = %s\n", tmp->red_out);
			printf("OUTFILE = %s|\n", tmp->outfile);
		}
		while (tmp->cmd[j] != NULL)
		{
			printf("cmd[%d] = %s|\n", j, tmp->cmd[j]);
			j++;
		}
		tmp = tmp->next;
		j = 0;
	}
}
//TOUT LES CHAR * AUTRE QUE CONTENT SONT DE SIMPLES POINTEURS SUR LES ELEMENTS EN QUESTION
//SI LE POINTEUR EST A NUL C'EST QUE L'ELEMENT N'EST PAS PRESENT, SINON CELA POINTE SUR LE PREMIERE CHAR DE L'ELEMENT
static t_exec_lst	*new_node(char *content)
{
	t_exec_lst	*new_node;
	
	new_node = malloc(sizeof(t_exec_lst));
	if (!new_node)
		return (NULL);
	new_node->content = ft_strdup(content);
	new_node->here_doc = NULL;
	new_node->heredoc_count = 0;
	new_node->limiter = NULL;
	new_node->append = NULL;
	new_node->red_in = NULL;
	new_node->infile = NULL;
	new_node->red_out = NULL;
	new_node->outfile = NULL;
	new_node->is_absolute_path = false;
	new_node->path_bin = NULL;
	new_node->cmd = NULL;
	new_node->next = NULL;
	return (new_node);
}

static t_exec_lst	*last_node(t_exec_lst *t)
{
	if (!t)
		return (NULL);
	while (t->next != NULL)
		t = t->next;
	return (t);
}

static void	add_back(t_exec_lst **t, t_exec_lst *new_node)
{
	t_exec_lst	*tmp;

	if (!(*t))
		*t = new_node;
	else
	{
		tmp = last_node(*t);
		tmp->next = new_node;
	}
}

void	build_lst(char *input, t_exec_lst **cmd)
{
	t_exec_lst	*node;
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