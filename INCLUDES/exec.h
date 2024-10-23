/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: annabrag <annabrag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 20:20:17 by art3mis           #+#    #+#             */
/*   Updated: 2024/10/23 22:00:45 by annabrag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# include "libraries.h"

/******************************************************************************\
 * BUILT-INS
\******************************************************************************/

// ft_exit.c
void			ft_exit(t_data *d, char **args);

// ft_env.c
int				ft_env(t_env_lst *env, char **args);

// ft_unset.c
int				ft_unset(t_data *d, char **args);

// ft_pwd.c
int				ft_pwd(void);

// ft_export_utils.c
void			add_var_to_exp_env(t_env_lst *e_env, char *var);
void			add_var_to_env(t_env_lst *env, char *var);
void			update_var_val(t_env_lst *to_up, t_env_lst *to_up_exp,
					t_env_lst *env, char *var);
t_env_lst		*search_for_var(t_env_lst *env, char *var);

// ft_export.c
int				ft_export(t_env_lst *exp_env, t_env_lst *env, char **args);

// ft_cd_utils.c
void			change_paths(t_env_lst *env, t_env_lst *exp_env);

// ft_cd.c
int				ft_cd(t_data *d);

// ft_echo.c
int				ft_echo(t_data *d, char **args);

// built_ins.c
bool			is_built_in(char **cmd);
int				execute_built_in(t_data *d, char **cmd);

/******************************************************************************\
 * EXECUTION
\******************************************************************************/

// exec_utils.c
char			*search_bin(char *cmd, char **tab_path);
char			**search_path(char **tab_path, char **env);
int				check_bin_path(t_exec_lst *node, bool absolute_path);
int				handle_bin_path(t_exec_lst *node, char **env);

// exec.c
void			exec(char *path_bin, char **cmd_and_args, char **env);
void			go_exec(t_exec_lst *node, char **env);

// here_doc.c
void			handle_heredoc(t_data *d, t_exec_lst **e_lst);

// pathfinder.c
void			pathfinder(t_data *d, t_exec_lst *node, char **env);

// while_cmd.c
void			while_cmd(t_data *d, t_exec_lst **e_lst);

#endif