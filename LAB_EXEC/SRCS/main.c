/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmateo <pmateo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 21:02:12 by pmateo            #+#    #+#             */
/*   Updated: 2024/09/02 19:47:35 by pmateo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../INCLUDES/mini_exec.h"

void	assign_flag(char *content, t_tok **node)
{
	
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
		if (input != NULL)
			free(input);
	}
	return (0);
}