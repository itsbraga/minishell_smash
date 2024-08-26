/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmateo <pmateo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 21:02:51 by pmateo            #+#    #+#             */
/*   Updated: 2024/08/26 16:27:04 by pmateo           ###   ########.fr       */
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
# include <linux/limits.h>
# include <errno.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "../LIBFT/INCLUDES/libft.h"
# include "../LIBFT/INCLUDES/ft_printf.h"
# include "../LIBFT/INCLUDES/get_next_line_bonus.h"
# include "defines.h"
# include "colors.h"
# include "my_features.h"

/******************************************************************************\
 * STRUCTS
\******************************************************************************/

// extern int		gsig_exit;

// typedef enum e_category
// {
// 	X = 1
// }				t_category;

// typedef struct s_input
// {
// 	t_category		type;
// 	char			*content;
// 	struct s_env	*next;
// }				t_input;

typedef struct s_token
{
	char			*content;
	struct s_token	*next;
}				t_token;

typedef struct s_env
{
	char			*content;
	struct s_env	*next;
}				t_env;

typedef struct s_global
{
	char		*input; // ira dans une fonction spe
	// t_input		*input;
	t_env		*env;
	t_env		*exp_env;
	t_token		*token;
	int			last_exit_status;
}				t_global;

/******************************************************************************\
 * INIT
\******************************************************************************/

void	init_global(t_global *global);

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

size_t	get_env_size(char **env);
t_env	*env_new_var(char *content);
void 	lstclear_env(t_env **env);
t_env	*copy_toppest(char **envp);
t_env	*ascii_sort(char **envp, char *last_added);
int		create_exp_env_list(t_env **exp_env, char **envp, size_t envp_size, size_t idx_exp_env);
int		create_env_list(t_env **env, char **envp);
void	create_env(t_global *g, char **envp);

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
void	del_current_token(t_token **t, t_token *cur);
size_t	get_tlist_size(t_token **t);
void	display_tokens(t_token *t);
bool	is_special_char(int c);

void	errmsg(char *cmd, char *arg);
int		errmsg_status(char *cmd, char *arg, int err_status);

/******************************************************************************\
 * BUILT-INS
\******************************************************************************/

void	exec_built_in(char **built_in, t_global *g);
int		my_pwd(void);
int 	go_to_env_var(t_global *g, char *var);
int		my_cd(t_global *g);
int		my_env(t_env *env);
void	my_exit(t_global *g, char **args);

#endif