/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_parsing.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmateo <pmateo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 21:02:51 by pmateo            #+#    #+#             */
/*   Updated: 2024/08/28 15:38:41 by pmateo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIEXEC_H
# define MINIEXEC_H

# include <stddef.h>
# include <stdio.h>
# include <unistd.h>
# include <sys/types.h>
# include <stdlib.h>
# include <stdbool.h>
# include <limits.h>
# include <errno.h>
# include <readline/readline.h>
# include "../LIBFT/INCLUDES/libft.h"
# include "../LIBFT/INCLUDES/ft_printf.h"
# include "../LIBFT/INCLUDES/get_next_line_bonus.h"

# define SUCCESS 0
# define FAILURE 1

typedef struct s_token
{
	int             idx;
	bool			to_expand;
    char			*content;
	struct s_token	*next;
}					t_token;

typedef struct s_exec
{
    char *input;
	char **envp;
}   t_exec;

void    init_e(t_exec *e);
t_token	*new_node(char *content);
t_token	*last_node(t_token *t);
void	add_back(t_token **t, t_token *new_node);
void	display_tokens(t_token *t);
size_t	get_tlist_size(t_token **t);
char	*handle_quotes_and_expand(char *input, char **envp);
char	*expand(char *str, char **envp);
char 	*search_var(char *to_find, char **envp);
bool	unclosed_quotes_return(bool closed[]);
char	*empty_quotes(char *str);
char	*del_empty_quotes(char *str, int quote_idx);
char	*del_quote_pair(char *str, int first, int second);
char	*take_var(char *str, char *var);
bool	switch_bool(bool closed);
int		find_closing_quote(char *str, char quote);

#endif