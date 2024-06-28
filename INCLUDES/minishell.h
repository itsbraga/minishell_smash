/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmateo <pmateo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 21:02:51 by pmateo            #+#    #+#             */
/*   Updated: 2024/06/28 15:31:17 by pmateo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stddef.h>
# include <stdio.h>
# include <unistd.h>
# include <sys/types.h>
# include <stdbool.h>
# include <stdlib.h>
# include <limits.h>
# include <errno.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "../LIBFT/INCLUDES/libft.h"
# include "../LIBFT/INCLUDES/ft_printf.h"
# include "../LIBFT/INCLUDES/get_next_line_bonus.h"
# include "colors.h"

//ERROR MACRO
# define MALLOC_ERR -1
# define PARSING_ERR -2
# define LEXER_ERR -3
# define EXPORT_ERR -4
# define EXEC_ERR -5
//PARSING MACRO
# define S_QUOTE_INSIDE 1
# define D_QUOTE_INSIDE 2
// struct token pour parsing et autres infos
typedef struct s_token
{
	int				idx;
	bool			to_expand;
	bool			s_quoted;
	bool			d_quoted;
	int				t_quoted;
	char			*content;
	struct s_token	*next;
}				t_token;

typedef struct s_global
{
	char		*input;
	char		**env;
	char		**export_env;
	t_token		*token;
}				t_global;


void	init_global(t_global *global);
// ENVIRONNEMENT
void	create_env(t_global *g, char **envp);
size_t	get_env_size(char **envp);
void	copy_toppest(t_global *g);
void	alpha_sort(t_global *g, char *current, size_t exp_env_index);

#endif