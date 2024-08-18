/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: annabrag <annabrag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 21:02:51 by pmateo            #+#    #+#             */
/*   Updated: 2024/08/16 17:44:27 by annabrag         ###   ########.fr       */
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
# include "defines.h"
# include "colors.h"

/******************************************************************************\
 * STRUCTS
\******************************************************************************/

typedef struct s_token
{
	int				idx;
	bool			to_expand;
	bool			s_quoted;
	bool			db_quoted;
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

/******************************************************************************\
 * INIT
\******************************************************************************/

void	init_global(t_global *global);
void	init_token(t_token *t);

/******************************************************************************\
 * PARSING
\******************************************************************************/

bool	is_closed_squote(char **str);
bool	is_closed_dbquote(char **str);
char	*squote(char **str);
char	*dbquote(char **str);
int		add_squote_content(char **str, t_token **t);
int		add_dbquote_content(char **str, t_token **t);
char	*cat_tcontent(t_token *to_cat);

/******************************************************************************\
 * ENVIRONMENT
\******************************************************************************/

void	create_env(t_global *g, char **envp);
size_t	get_env_size(char **envp);
void	copy_toppest(t_global *g);
void	alpha_sort(t_global *g, char *current, size_t exp_env_index);

/******************************************************************************\
 * EXPAND
\******************************************************************************/


/******************************************************************************\
 * TOOLS
\******************************************************************************/

t_token	*new_node(char *content);
t_token	*t_last_node(t_token *t);
void	add_back(t_token **t, t_token *new_node);
void	clear_tokens(t_token **t);
void	delone_token(t_token *t);
void	delcurrent_token(t_token **t, t_token *cur);
bool	is_special_char(int c);

/******************************************************************************\
 * BUILTINS
\******************************************************************************/

int		my_pwd(void);

#endif