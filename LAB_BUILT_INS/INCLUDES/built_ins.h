/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_ins.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: annabrag <annabrag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 14:11:16 by annabrag          #+#    #+#             */
/*   Updated: 2024/08/20 20:30:03 by annabrag         ###   ########.fr       */
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
# include <linux/limits.h>
# include <errno.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "../LIBFT/INCLUDES/libft.h"
# include "../LIBFT/INCLUDES/ft_printf.h"
# include "../LIBFT/INCLUDES/get_next_line_bonus.h"
# include "colors.h"

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
}				t_global;


/******************************************************************************\
 * FUNCTIONS
\******************************************************************************/

t_env		*e_new_node(char *content);
t_env		*e_last_node(t_env *e);
void		e_add_back(t_env **e, t_env *new_node);
void		create_env_list(t_env *env, char **envp);
void		display_env(t_env *env);

t_token		*new_node(char *content);
t_token		*t_last_node(t_token *t);
void		add_back(t_token **t, t_token *new_node);
void		display_tokens(t_token *t);
void		clear_tokens(t_token **t);

int			my_pwd(void);
void		exec_built_in(char **built_in, t_global *g);
int			my_cd(t_global *g);

#endif