/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: art3mis <art3mis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 21:02:51 by pmateo            #+#    #+#             */
/*   Updated: 2024/11/04 02:48:10 by art3mis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libraries.h"

/*	To be used only to indicate a received signal.
	The signal handler must not access our main data structures.
*/
extern int		g_sig_code;

/******************************************************************************\
 * ENVIRONMENT
\******************************************************************************/

// export_env_utils.c
int				cmp_to_equal(const char *s1, const char *s2);
t_env_lst		*copy_toppest(char **envp);
t_env_lst		*ascii_sort(char **envp, char *last_added);
char			*add_quotes_to_value(char *var);
t_env_lst		*exp_env_new_var(char *content);

// env_utils.c
void			update_shlvl_export(t_env_lst **exp_env);
void			update_shlvl(t_env_lst **env);
size_t			get_env_tab_size(char **env);
char			**recreate_env_tab(t_env_lst **env);

// create_env.c
int				create_exp_env_list(t_env_lst **exp_env, char **envp,
					size_t envp_size, size_t idx_exp_env);
int				create_env_list(t_env_lst **env, char **envp);
void			create_env(t_data *d, char **envp);

/******************************************************************************\
 * SIGNALS
\******************************************************************************/

// signals_here_doc.c
void			set_signals_in_heredoc(void);

// signals.c
void			sigquit_handler(int signo);
void			set_signals(void);
void			set_signals_in_exec(void);

/******************************************************************************\
 * INIT
\******************************************************************************/

// prompt_utils.c
void			part_one(t_prompt *pr);
void			custom_cwd(t_prompt *pr);
char			*substract_path(t_prompt *pr);

// prompt.c
char			*generate_prompt(t_prompt *pr, t_data *d);
void			update_prompt(t_data *d, t_prompt *pr);
void			rl_reset_custom_prompt(void);

// init_data.c
t_data			*data_struct(void);

#endif