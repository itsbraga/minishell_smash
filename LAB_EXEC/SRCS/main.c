/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: art3mis <art3mis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 21:02:12 by pmateo            #+#    #+#             */
/*   Updated: 2024/06/24 16:28:11 by art3mis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../INCLUDES/mini_exec.h"

t_token	*ft_lstnew(char *content)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	token->content = content;
    token->pos = NULL;
	token->next = NULL;
	return (token);
}

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*tmp;

	if (!*lst)
		*lst = new;
	else
	{
		tmp = ft_lstlast(*lst);
		tmp->next = new;
	}
}

void    fill_token_list(t_token **token, t_exec *e)
{
    char **cmd_tab;
    t_token *new_token;

    cmd_tab = ft_split(e->input, ' ');
    if (!cmd_tab)
        exit(EXIT_FAILURE);
    while (cmd_tab)
    {
        new_token = 
    }
}

void    exec(t_token **token, t_exec *e)
{
    
}

int main(int argc, char **argv, char **envp)
{
    t_exec e;
    t_token *token;
    
    if (argc > 1)
        exit(EXIT_FAILURE);
    (void)argv;
    init_e(&e);
	e.envp = envp;
    while (1)
    {
        ft_printf(1, "@_@ $> ");
        e.input = get_next_line(0, NULL);
		// if (e.input)
		// 	add_history(e.input);
        fill_token_list(&token, &e);
        exec(&token, &e);
    }
    return (0);
}