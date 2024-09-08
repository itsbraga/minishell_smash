/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmateo <pmateo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 21:02:12 by pmateo            #+#    #+#             */
/*   Updated: 2024/09/08 22:56:32 by pmateo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../INCLUDES/mini_exec.h"

void	lstclear_tokens(t_tok **t)
{
	t_tok	*tmp;
	
	if (t == NULL || (*t) == NULL)
		return ;
	while ((*t) != NULL)
	{
		tmp = (*t)->next;
		free((*t)->content); 
		free(*t);
		(*t) = tmp;
	}
	(*t) = NULL;
}

size_t	len_to_char(char *str, char c)
{
	size_t i;

	i = 0;
	while (str[i] != c && str[i] != '\0')
		i++;
	return (i);
}
void	assign_cmd(char *str, t_tok **node)
{
	printf("in assign cmd = %s\n", str);
	(*node)->cmd = ft_split(str, ' ');
}

void	assign_heredoc(char *str, t_tok **node)
{
	int	i;

	i = 2;
	printf("cc");
	(*node)->here_doc = str;
	while (!((str[i] >= 'A' && str[i] <= 'Z') 
			|| (str[i] >= 'a' && str[i] <= 'z')))
		i++;
	(*node)->limiter = ft_strldup(&str[i], (len_to_char(str, ' ') + 1));
	while ((str[i] >= 'A' && str[i] <= 'Z')
			|| (str[i] >= 'a' && str[i] <= 'z'))
		i++;
	assign_cmd(ft_strdup(&str[i]), node);
}

void	assign_append(char *str, char *append, t_tok **node)
{
	int	i;

	i = 0;
	(*node)->append = append;
	if ((*node)->cmd == NULL)
		assign_cmd(ft_strldup(str, len_to_char(str, '>')), node);
	while (!((append[i] >= 'A' && append[i] <= 'Z')
			|| (append[i] >= 'a' && append[i] <= 'z')))
		i++;
	(*node)->outfile = ft_strldup(&append[i], len_to_char(&append[i], ' ') + 1);
}

void	assign_red_in(char *str, char *red_in, t_tok **node)
{
	int i;

	i = 0;
	(*node)->red_in = red_in;
	if ((*node)->cmd == NULL)
		assign_cmd(ft_strldup(str, len_to_char(str, '<')), node);
	while (!((red_in[i] >= 'A' && red_in[i] <= 'Z')
			|| (red_in[i] >= 'a' && red_in[i] <= 'z')))
		i++;
	(*node)->infile = ft_strldup(&red_in[i], len_to_char(&red_in[i], ' '));
}

void	assign_red_out(char *str, char *red_out, t_tok **node)
{
	int	i;

	i = 0;
	(*node)->red_out = red_out;
	if ((*node)->cmd == NULL)
		assign_cmd(ft_strldup(str, len_to_char(str, '>')), node);
	while (!((red_out[i] >= 'A' && red_out[i] <= 'Z')
			|| (red_out[i] >= 'a' && red_out[i] <= 'z')))
		i++;
	(*node)->outfile = ft_strldup(&red_out[i], len_to_char(&red_out[i], ' '));
}

void	assign_flag(char *str, t_tok **node)
{
	int	i;
	
	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '<' && str[i + 1] == '<')
			assign_heredoc(&str[i], node);
		else if (str[i] == '>' && str[i + 1] == '>')
			assign_append(str, &str[i], node);
		else if (str[i] == '<' && str[i - 1] != '<' && str[i + 1] != '<')
			assign_red_in(str, &str[i], node);
		else if (str[i] == '>' && str[i - 1] != '>' && str[i + 1] != '>')
			assign_red_out(str, &str[i], node);
		i++;
	}
	if ((*node)->here_doc == NULL && (*node)->append == NULL
		&& (*node)->red_in == NULL && (*node)->red_out == NULL)
		assign_cmd(str, node);
}

void	token_recognition(t_tok **cmd)
{
	t_tok *node;

	node = *cmd;
	while (node != NULL)
	{
		assign_flag(node->content, &node);
		node = node->next;
	}
}

int	main(int argc, char **argv, char **envp)
{
	char *input;
	t_tok	*cmd;
	
	if (argc > 1)
		exit(FAILURE);
	(void)argv;
	(void)envp;
	cmd = NULL;
	while (1)
	{
		input = readline("mini_exec> ");
		build_lst(input, &cmd);
		display_tokens(cmd);
		token_recognition(&cmd);
		display_tokens_with_infos(cmd);
		lstclear_tokens(&cmd);
		if (input != NULL)
			free(input);
	}
	return (0);
}

// "cat < infile > outfile"