/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: art3mis <art3mis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 21:02:51 by pmateo            #+#    #+#             */
/*   Updated: 2024/09/16 01:07:32 by art3mis          ###   ########.fr       */
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
# include "structs.h"
# include "defines.h"
# include "colors.h"

/******************************************************************************\
 * GLOBAL VARIABLE
\******************************************************************************/

/*	The global variable have to be used only to indicate a received signal.
	Consider the implications: this approach ensures that your signal handler
	will not access your main data structures.
*/
extern int	g_sig_code;

/******************************************************************************\
 * INIT
\******************************************************************************/

// init_global.c
void		init_global(t_global *global);

/******************************************************************************\
 * LEXING
\******************************************************************************/

// token_utils.c
void			del_current_token(t_token_dblst **t, t_token_dblst *to_delete);
size_t			get_token_dblst_size(t_token_dblst **t);
void			token_dblst_add_back(t_token_dblst **t,
t_token_dblst *new_node);
t_token_dblst	*token_dblst_new_node(char *content, t_token_type type);

// check_main_lst.c
char			**split_main_content(t_main_lst *main);

// identify_token.c
t_token_type	classify_token(char *token, char *prev);
void			lst_tokenization(t_token_dblst *t);

// create_token_lst.c
int				create_token_dblst(t_main_lst *main, t_token_dblst **t);

/******************************************************************************/

// main_lst_utils.c
size_t			get_main_lst_size(t_main_lst **main);
void			main_lst_add_back(t_main_lst **main, t_main_lst *new_node);
t_main_lst		*main_lst_new_node(char *content);

// check_input.c
char			**split_user_input(char *input);

// create_main_lst.c
int				create_main_lst(t_global *g, char *user_input);
int 			del_unwanted_char(t_main_lst *main);

/******************************************************************************\
 * PARSING
\******************************************************************************/

// del_quotes.c
char		*del_empty_quotes(char *str, int quote_idx);
char		*del_quote_pair(char *str, int first, int second);

// quotes_utils.c
bool		switch_bool(bool closed);
int			find_closing_quote(char *str, char quote);
bool		unclosed_quotes_return(bool closed[]);

// handle_quotes.c
bool		unclosed_quotes(char *str);
char		*empty_quotes(char *str);
char		*handle_quotes_modif(char *user_input);

/******************************************************************************\
 * ENVIRONMENT
\******************************************************************************/

// export_env_utils.c
size_t		get_env_size(char **env);
t_env_lst	*copy_toppest(char **envp);
t_env_lst	*ascii_sort(char **envp, char *last_added);

// env_utils.c
t_env_lst	*env_new_var(char *content);
void		del_env_var(t_env_lst **env, char *var_to_rm);

// create_env.c
int			create_exp_env_list(t_env_lst **exp_env, char **envp, size_t envp_size,
size_t idx_exp_env);
int			create_env_list(t_env_lst **env, char **envp);
void		create_env(t_global *g, char **envp);

/******************************************************************************\
 * EXPAND
\******************************************************************************/

// expand_utils.c
size_t		len_to_equal(char *str);
char		*take_var_value(char *str);
char		*take_var(char *str, char *var);
char 		*search_var(char *to_find, t_env_lst *env);

// expand.c
char		*expand(t_global *g, char *str);

/******************************************************************************\
 * BUILT-INS
\******************************************************************************/

// my_unset.c
int			my_unset(t_global *g, char **args);

// my_exit.c
void		my_exit(t_global *g, char **args);

// my_cd_utils.c
void		change_paths(t_env_lst *env, t_env_lst *exp_env);

// my_cd.c
int			my_cd(t_global *g);

// my_pwd.c
int			my_pwd(void);

// my_env.c
int			my_env(t_env_lst *env);

// built_ins.c
void		exec_built_in(char **built_in, t_global *g);

/******************************************************************************\
 * TOOLS
\******************************************************************************/

// clean_exit_shell.c
void		clean_exit_shell(t_global *g, int err_status);

// cleanup.c
void		free_tab(char **tab);
void		lstclear_tokens(t_token_dblst **t);
void		lstclear_main(t_main_lst **main);
void 		lstclear_env(t_env_lst **env);
void		free_global(t_global *g, bool clear_history);

// error.c
void		err_msg(char *detail, char *reason, int quotes);
int			err_msg_cmd(char *cmd, char *detail, char *reason, int err_status);

/******************************************************************************\
 * EXTRAS
\******************************************************************************/

// display.c
void		display_export_env(t_env_lst *exp_env);
void		display_main_lst(t_main_lst *main);
void		display_token_dblst(t_token_dblst *t);

// features.c
void		rainbow_txt(const char *str);
void		rainbow_txt_nonl(const char *str);
char		*rainbow_prompt(const char *str);

#endif