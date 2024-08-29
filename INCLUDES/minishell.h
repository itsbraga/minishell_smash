/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: annabrag <annabrag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 21:02:51 by pmateo            #+#    #+#             */
/*   Updated: 2024/08/29 18:52:02 by annabrag         ###   ########.fr       */
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

typedef enum 	e_category
{
	WORD,
	SEPARATOR,
}			 	t_category;

// typedef struct s_input
// {
// 	t_category		type;
// 	char			*content;
// 	struct s_env	*next;
// }				t_input;

typedef struct s_env
{
	char			*content;
	struct s_env	*next;
}				t_env;

typedef struct s_token
{
	char			*content;
	struct s_token	*next;
}				t_token;

typedef struct s_global
{
	char		*prompt;
	char		*input; // ira dans une fonction spe
	// t_input		*input;
	t_env		*env;
	t_env		*exp_env;
	t_token		*token;
}				t_global;

// typedef struct s_command
// {
// 	char				*cmd;
// 	char				**args;
// 	struct s_command	*next;
// }				t_command;

/******************************************************************************\
 * GLOBAL VARIABLE
\******************************************************************************/

extern int	g_last_exit_status;

/******************************************************************************\
 * INIT
\******************************************************************************/

void	init_global(t_global *global);

/******************************************************************************\
 * PARSING
\******************************************************************************/

// ?
char	*cat_tcontent(t_token *to_cat);

/******************************************************************************\
 * ENVIRONMENT
\******************************************************************************/

// env_utils.c
t_env	*env_new_var(char *content);

// create_export_env.c
size_t	get_env_size(char **env);
t_env	*copy_toppest(char **envp);
t_env	*ascii_sort(char **envp, char *last_added);
int		create_exp_env_list(t_env **exp_env, char **envp, size_t envp_size,
size_t idx_exp_env);

// create_env.c
int		create_env_list(t_env **env, char **envp);
void	create_env(t_global *g, char **envp);

/******************************************************************************\
 * EXPAND
\******************************************************************************/


/******************************************************************************\
 * BUILT-INS
\******************************************************************************/

// my_exit.c
void	my_exit(t_global *g, char **args);

// my_cd_utils.c
char	*find_var_path(char *to_find, t_env *env);
int 	go_to_env_var(t_global *g, char *var);

// my_cd.c
int		my_cd(t_global *g);

// my_pwd.c
int		my_pwd(void);

// my_env.c
int		my_env(t_env *env);

// built_ins.c
void	exec_built_in(char **built_in, t_global *g);

/******************************************************************************\
 * TOOLS
\******************************************************************************/

// token_utils.c
size_t	get_tlist_size(t_token **t);
void	add_back(t_token **t, t_token *new_node);
t_token	*last_node(t_token *t);
t_token	*new_node(char *content);

// display.c
void    display_export_env(t_env *exp_env);
void	display_tokens(t_token *t);

// err_msg.c
void	errmsg(char *cmd, char *arg);
int		errmsg_exit_status(char *cmd, char *arg, int err_status);
// int		errmsg_exit_status(t_global *g, char *cmd, char *arg, int err_status,
// bool cleanup);

// cleanup.c
void	del_current_token(t_token **t, t_token *cur);
void	lstclear_tokens(t_token **t);
void 	lstclear_env(t_env **env);
void    free_global(t_global *g, bool clear_history);
void	free_tab(char **tab);

// clean_exit_shell.c
void	clean_exit_shell(t_global *g, int err_status);

// features.c
void	rainbow_txt(const char *str);
void	rainbow_txt_nonl(const char *str);
char	*rainbow_prompt(const char *str);


#endif