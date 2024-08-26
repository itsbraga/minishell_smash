/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmateo <pmateo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 21:02:51 by pmateo            #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2024/08/26 19:34:56 by annabrag         ###   ########.fr       */
=======
<<<<<<< HEAD
/*   Updated: 2024/08/26 16:27:04 by pmateo           ###   ########.fr       */
=======
/*   Updated: 2024/08/26 16:24:23 by annabrag         ###   ########.fr       */
>>>>>>> 6e6a8733545fee32380e072c25f1579acc0c37b4
>>>>>>> 331b04d903f2a2b001b4dd4fcb2fdae6e653d3e1
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

typedef enum e_category
{
	WORD,
	SEPARATOR,
}			 t_category;

// typedef struct s_input
// {
// 	t_category		type;
// 	char			*content;
// 	struct s_env	*next;
// }				t_input;

<<<<<<< HEAD
typedef struct s_env
=======
<<<<<<< HEAD
=======
typedef struct s_global
>>>>>>> 331b04d903f2a2b001b4dd4fcb2fdae6e653d3e1
{
	char			*content;
	struct s_env	*next;
} 				t_env;

>>>>>>> 6e6a8733545fee32380e072c25f1579acc0c37b4
typedef struct s_token
{
	char			*content;
	struct s_token	*next;
}				t_token;

typedef struct s_global
{
	char		*input; // ira dans une fonction spe
	// t_input		*input;
	t_env		*env;
	t_env		*exp_env;
	t_token		*token;
	int			last_exit_status;
}				t_global;

// typedef struct s_command
// {
// 	char				*cmd;
// 	char				**args;
// 	struct s_command	*next;
// }				t_command;

<<<<<<< HEAD
=======
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

>>>>>>> 331b04d903f2a2b001b4dd4fcb2fdae6e653d3e1
/******************************************************************************\
 * GLOBAL VARIABLE
\******************************************************************************/

extern int		gsig_exit_status;

/******************************************************************************\
 * INIT
\******************************************************************************/

void	init_global(t_global *global);

/******************************************************************************\
 * PARSING
\******************************************************************************/

// ?
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

<<<<<<< HEAD
// create_env_export.c
size_t	get_env_size(char **env);
t_env	*copy_toppest(char **envp);
t_env	*ascii_sort(char **envp, char *last_added);
int		create_exp_env_list(t_env **exp_env, char **envp, size_t envp_size, size_t idx_exp_env);
=======
<<<<<<< HEAD
size_t	get_env_size(char **env);
t_env	*env_new_var(char *content);
void 	lstclear_env(t_env **env);
t_env	*copy_toppest(char **envp);
t_env	*ascii_sort(char **envp, char *last_added);
int		create_exp_env_list(t_env **exp_env, char **envp, size_t envp_size, size_t idx_exp_env);
int		create_env_list(t_env **env, char **envp);
void	create_env(t_global *g, char **envp);
=======
void	lstclear_env(t_env **env);
>>>>>>> 331b04d903f2a2b001b4dd4fcb2fdae6e653d3e1
t_env	*env_new_var(char *content);

// create_env.c
int		create_env_list(t_env **env, char **envp);
<<<<<<< HEAD
void	create_env(t_global *g, char **envp);
=======
>>>>>>> 6e6a8733545fee32380e072c25f1579acc0c37b4
>>>>>>> 331b04d903f2a2b001b4dd4fcb2fdae6e653d3e1

/******************************************************************************\
 * EXPAND
\******************************************************************************/


/******************************************************************************\
 * BUILT-INS
\******************************************************************************/

void	my_exit(t_global *g, char **args);
int		my_cd(t_global *g);
int 	go_to_env_var(t_global *g, char *var);
int		my_pwd(void);
int		my_env(t_env *env);
void	exec_built_in(char **built_in, t_global *g);

/******************************************************************************\
 * TOOLS
\******************************************************************************/

// token_utils.c
size_t	get_tlist_size(t_token **t);
void	display_tokens(t_token *t);
void	add_back(t_token **t, t_token *new_node);
t_token	*last_node(t_token *t);
t_token	*new_node(char *content);

// error.c
int		errmsg_status(char *cmd, char *arg, int err_status);
void	errmsg(char *cmd, char *arg);

// free.c
void	lstclear_tokens(t_token **t);
void	del_current_token(t_token **t, t_token *cur);
void 	lstclear_env(t_env **env);
void	free_tab(char **tab);


#endif