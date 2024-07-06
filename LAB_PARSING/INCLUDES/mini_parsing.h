/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_parsing.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmateo <pmateo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 21:02:51 by pmateo            #+#    #+#             */
/*   Updated: 2024/07/06 14:29:27 by pmateo           ###   ########.fr       */
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
# include "../LIBFT/INCLUDES/libft.h"
# include "../LIBFT/INCLUDES/ft_printf.h"
# include "../LIBFT/INCLUDES/get_next_line_bonus.h"

# define MALLOC_ERR -1
# define PARSING_ERR -2
# define LEXER_ERR -3
# define EXP_ERR -4
# define EXEC_ERR -5
# define TRUE 1
# define FALSE 0
# define UNCLOSED_QUOTE -1

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
t_token	*t_last_node(t_token *t);
void	add_back(t_token **t, t_token *new_node);
void	display_tokens(t_token *t);
size_t	get_tlist_size(t_token **t);
void	handle_quotes(t_token **t);

#endif