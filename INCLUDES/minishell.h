/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: annabrag <annabrag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 21:02:51 by pmateo            #+#    #+#             */
/*   Updated: 2024/10/08 19:25:18 by annabrag         ###   ########.fr       */
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
# include <sys/stat.h>
# include <sys/wait.h>

# include "../LIBFT/INCLUDES/libft.h"
# include "../LIBFT/INCLUDES/ft_printf.h"
# include "../LIBFT/INCLUDES/get_next_line_bonus.h"
# include "structs.h"
# include "garbage_collector.h"
# include "defines.h"
# include "colors.h"

/******************************************************************************\
 * GLOBAL VARIABLE
\******************************************************************************/

/*	The global variable have to be used only to indicate a received signal.
	Consider the implications: this approach ensures that your signal handler
	will not access your main data structures.
*/
extern int		g_sig_code;

/******************************************************************************\
 * INIT
\******************************************************************************/

// init_data.c
t_data			*data_struct(void);

/******************************************************************************\
 * LEXING
\******************************************************************************/

// check_input.c
void			parse_input(t_parser *p);

// create_main_lst.c
int				create_main_lst(t_data *d, char *user_input);

// check_main.c
void			parse_segment(t_token_parser *p);

// create_token_lst.c
int				create_token_dblst(t_data *d);

// tokenization.c
void			lst_tokenization(t_token_dblst *t);

/******************************************************************************\
 * PARSING
\******************************************************************************/

// quotes_utils.c
bool			switch_bool(bool closed);
int				find_closing_quote(char *str, char quote);
bool			unclosed_quotes_return(bool closed[]);
char			*del_empty_quotes(char *str, int quote_idx);
char			*del_quote_pair(char *str, int first, int second);

// handle_quotes.c
bool			unclosed_quotes(char *str);
char			*empty_quotes(char *str);
char			*other_quotes(char *str);

// check_sequence.c
int				check_redir_sequence(char *content);

// exec_lst_utils.c
char			*token_cleanup(char *content);
int				cmd_token_count(t_token_dblst *t);

// create_redir_lst.c
int				create_redir_lst(t_data *d);

// create_exec_lst.c
int				create_exec_lst(t_data *d);

/******************************************************************************\
 * ENVIRONMENT
\******************************************************************************/

// export_env_utils.c
t_env_lst		*copy_toppest(char **envp);
t_env_lst		*ascii_sort(char **envp, char *last_added);

// env_utils.c
size_t			get_envlst_size(t_env_lst **env);
size_t			get_envtab_size(char **env);
t_env_lst		*env_new_var(char *content);
void			del_env_var(t_env_lst **env, char *var_to_rm);
char			**recreate_env_tab(t_env_lst **env);

// create_env.c
int				create_exp_env_list(t_env_lst **exp_env, char **envp,
size_t envp_size, size_t idx_exp_env);
int				create_env_list(t_env_lst **env, char **envp);
void			create_env(t_data *d, char **envp);

/******************************************************************************\
 * EXPANSION
\******************************************************************************/

// expand_utils.c
size_t			len_to_equal(char *str);
char			*clean_translated_variable(char *str, char *var);
char			*take_var(char *str, char *var);
char 			*search_var(char *to_find, t_env_lst *env);

// expand.c
char			*expand(t_data *d, char *str, bool in_heredoc);

/******************************************************************************\
 * BUILT-INS
\******************************************************************************/

// ft_exit.c
void			ft_exit(t_data *d, char **args);

// ft_env.c
int				ft_env(t_env_lst *env);

// ft_unset.c
int				ft_unset(t_data *d, char **args);

// ft_pwd.c
int				ft_pwd(void);

// cd_utils.c
void			change_paths(t_env_lst *env, t_env_lst *exp_env);

// ft_cd.c
int				ft_cd(t_data *d);

// ft_echo.c
int				ft_echo(char **args);

// built_ins.c
void			exec_built_in(char **built_in, t_data *d);

/******************************************************************************\
 * EXECUTION
\******************************************************************************/

// exec_utils.c
char			*search_bin(char *cmd, char **tab_path);
char			**search_path(char **tab_path, char **env);
 int			check_bin_path(t_exec_lst *node, bool absolute_path);
int				handle_bin_path(t_exec_lst *node, char **env);


// exec.c
void			exec(char *path_bin, char **cmd_and_args, char **env);
void			go_exec(t_exec_lst *node, char **env);

// here_doc.c
int				fill_all_heredoc(t_data *d, t_redir_lst *r);

// pathfinder.c
void			pathfinder(t_data *d, t_exec_lst *node, char **env);

// while_cmd.c
void			while_cmd(t_data *d, t_exec_lst **e_lst);

/******************************************************************************\
 * TOOLS
\******************************************************************************/

// error.c
void			err_msg(char *detail, char *reason, int quotes);
int				err_msg_cmd(char *cmd, char *detail, char *reason,
int err_status);

// garbage*.c ---> garbage_collector.h

// secure_malloc.c
void    		secure_malloc(void *to_secure);
void			secure_malloc2(void *to_secure, bool full_clean);

// lstclear.c
void			lstclear_main(t_main_lst **main);
void			lstclear_token(t_token_dblst **t);
void			lstclear_redir(t_redir_lst **r);
void			lstclear_exec(t_exec_lst **e);
void 			lstclear_env(t_env_lst **env);

// cleanup.c
void			free_data(t_data *d, bool clear_history);
void			clean_exit_shell(int err_status);

/******************************************************************************\
 * TOOLS/LISTS
\******************************************************************************/

// main_lst.c
size_t			get_main_lst_size(t_main_lst **main);
void			main_lst_add_back(t_main_lst **main, t_main_lst *new_node);
t_main_lst		*main_lst_new_node(char *content);

// token_dblst.c
void			del_current_token(t_token_dblst **t, t_token_dblst *to_delete);
size_t			get_token_dblst_size(t_token_dblst **t);
void			token_dblst_add_back(t_token_dblst **t,
t_token_dblst *new_node);
t_token_dblst	*token_dblst_new_node(char *content, t_token_type type);

// redir_lst.c
bool			is_redir(char *str);
size_t			get_redir_lst_size(t_redir_lst **r);
void			redir_lst_add_back(t_redir_lst **r, t_redir_lst *new_node);
t_redir_lst 	*redir_lst_new_node(t_token_type type);

// exec_lst.c
size_t			get_exec_lst_size(t_exec_lst **e);
void			exec_lst_add_back(t_exec_lst **e, t_exec_lst *new_node);
t_exec_lst 		*exec_lst_new_node(void);

/******************************************************************************\
 * EXTRAS
\******************************************************************************/

// display.c
void			display_export_env(t_env_lst *exp_env);
void			display_main_lst(t_main_lst *main);
void			display_token_dblst(t_token_dblst *t);
void    		display_redir_lst(t_redir_lst *r);

// features.c
void			rainbow_txt(const char *str);
void			rainbow_txt_nonl(const char *str);
char			*rainbow_prompt(const char *str);

#endif