/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmateo <pmateo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 21:02:51 by pmateo            #+#    #+#             */
/*   Updated: 2024/06/26 19:18:19 by pmateo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stddef.h>
# include <stdio.h>
# include <unistd.h>
# include <sys/types.h>
# include <stdlib.h>
# include <limits.h>
# include <errno.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "../LIBFT/INCLUDES/libft.h"
# include "../LIBFT/INCLUDES/ft_printf.h"
# include "../LIBFT/INCLUDES/get_next_line_bonus.h"
# include "colors.h"

# define MALLOC_ERR -1
# define PARSING_ERR -2
# define LEXER_ERR -3
# define EXPORT_ERR -4
# define EXEC_ERR -5
# define TRUE 1
# define FALSE 0

// struct token pour parsing et autres infos
typedef struct s_token
{
	char			*content;
	int				idx;
	struct s_token	*next;
}				t_token;

typedef struct s_global
{
	char		*input;
	char		**env;
	char		**export_env;
	t_token		*token;
}				t_global;

// struct exec

void	init_global(t_global *global);
void	create_env(t_global *g, char **envp);
size_t	get_env_size(char **envp);
void	copy_toppest(t_global *g);
void	alpha_sort(t_global *g, char *current, size_t exp_env_index);

#endif