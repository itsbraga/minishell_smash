/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_ins.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: annabrag <annabrag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 14:11:16 by annabrag          #+#    #+#             */
/*   Updated: 2024/08/26 19:29:27 by annabrag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILT_INS_H
# define BUILT_INS_H

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
# include "colors.h"
# include "my_features.h"

# ifndef PATH_MAX
#  define PATH_MAX 4096
# endif

/******************************************************************************\
 * EXIT STATUS
\******************************************************************************/

# define SUCCESS 0
# define FAILURE 1
# define MISUSE_BUILTIN 2
# define CMD_CANNOT_EXEC 126
# define CMD_NOT_FOUND 127
# define CTRL_C_EXIT 130 // 128 + signal 2 (SIGINT)
# define KILL_EXIT 143 // 128 + signal 15 (SIGTERM)
# define OUT_OF_RANGE 255

/******************************************************************************\
 * STRUCTS
\******************************************************************************/

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
	char		*input;
	t_env		*env;
	t_token		*token;
	int			last_exit_status;
}				t_global;

/******************************************************************************\
 * FUNCTIONS
\******************************************************************************/

t_env		*env_new_var(char *content);
void		lstclear_env(t_env **env);
int			create_env_list(t_env **env, char **envp);

t_token		*new_node(char *content);
t_token		*last_node(t_token *t);
void		add_back(t_token **t, t_token *new_node);
void		lstclear_tokens(t_token **t);
void		display_tokens(t_token *t);

void		exec_built_in(char **built_in, t_global *g);
int			my_pwd(void);
int 		go_to_env_var(t_global *g, char *var);
int			my_cd(t_global *g);
int			my_env(t_env *env);
int			my_exit(t_global *g, char **args);

void		errmsg(char *cmd, char *arg);
int			errmsg_status(char *cmd, char *arg, int err_status);

void		free_tab(char **tab);

/******************************************************************************\
 * TESTS
\******************************************************************************/

#endif