/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmateo <pmateo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 21:02:12 by pmateo            #+#    #+#             */
/*   Updated: 2024/06/24 03:10:47 by pmateo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../INCLUDES/mini_exec.h"

t_tlist	*ft_lstnew(char *content)
{
	t_tlist	*token;

	token = malloc(sizeof(t_tlist));
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

void    fill_tlist(t_tlist **token, t_exec *e)
{
    char **cmd_tab;
    t_tlist *new_token;

    cmd_tab = ft_split(e->input, ' ');
    if (!cmd_tab)
        exit(EXIT_FAILURE);
    while (cmd_tab)
    {
        new_token = 
    }
}

void    exec(t_tlist **token, t_exec *e)
{
    
}

int main(int argc, char **argv, char **envp)
{
    t_exec e;
    t_tlist *token;
    
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
        fill_tlist(&token, &e);
        exec(&token, &e);
    }
    return (0);
}