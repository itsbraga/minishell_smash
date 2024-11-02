/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: annabrag <annabrag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 20:20:17 by art3mis           #+#    #+#             */
/*   Updated: 2024/11/02 19:48:23 by annabrag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# include "libraries.h"

/******************************************************************************\
 * BUILT-INS
\******************************************************************************/

// ft_exit.c
int				ft_exit(char **args);

// ft_env.c
int				ft_env(t_env_lst **env, char **args);

// ft_unset.c
int				ft_unset(t_data *d, char **args);

// ft_pwd.c
int				ft_pwd(char **args);

// ft_export_utils.c
void			add_var_to_exp_env(t_env_lst **e_env, char *var);
void			add_var_to_env(t_env_lst **env, char *var);
void			update_var_val(t_env_lst *to_up, t_env_lst *to_up_exp,
					t_env_lst **env, char *var);
t_env_lst		*search_for_var(t_env_lst **env, char *var);

// ft_export.c
int				ft_export(t_env_lst **exp_env, t_env_lst **env, char **args);

// ft_cd_utils.c
void			change_paths(t_env_lst **env, t_env_lst **exp_env);
int				is_directory(const char *path);

// ft_cd.c
// int				ft_cd(t_data *d);
int				ft_cd(t_data *d, char **args);

// ft_echo.c
int				ft_echo(char **args);

// built_ins.c
bool			is_built_in(char **cmd);
int				execute_child_built_in(t_data *d, char **cmd);
int				execute_parent_built_in(t_data *d, char **cmd);

/******************************************************************************\
 * EXECUTION
\******************************************************************************/

// exec_utils2.c
void			close_hd_all_nodes(t_data *d);
void			close_hd_other_nodes(t_data *d, t_exec_lst *node);
bool			check_if_is_dir(char *bin_path);
char			**search_path(char **tab_path, char **env);

// exec_utils.c
char			*search_bin(char *cmd, char **tab_path);
int				check_built_path(t_exec_lst *node);
int				check_given_path(t_exec_lst *node);

// exec.c
void			execute(char *path_bin, char **cmd_and_args, char **env);
int				handle_bin_path(t_exec_lst *node, char **env);
void			go_exec(t_exec_lst *node);

// here_doc.c
int				handle_heredoc(t_data *d, t_exec_lst **e_lst);

// here_doc_utils.c
int				open_heredoc(t_data *d, char *limiter);

// pathfinder.c
void			pathfinder(t_data *d, t_exec_lst *node);

// while_cmd.c
void			while_cmd(t_data *d, t_exec_lst **e_lst);

#endif