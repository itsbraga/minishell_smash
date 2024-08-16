/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: annabrag <annabrag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 14:11:16 by annabrag          #+#    #+#             */
/*   Updated: 2024/08/16 16:13:56 by annabrag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

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

typedef struct s_token
{
	int				idx;
	bool			to_expand;
	bool			s_quoted;
	bool			db_quoted;
	int				t_quoted;
	char			*content;
	struct s_token	*next;
}				t_token;

typedef struct s_global
{
	char		*input;
	char		**env;
	char		**export_env;
	t_token		*token;
}				t_global;

size_t		get_env_size(char **envp);
void		copy_toppest(t_global *g);
void		alpha_sort(t_global *g, char *current, size_t exp_env_index);
void		create_env(t_global *g, char **envp);
t_token		*new_node(char *content);
t_token		*t_last_node(t_token *t);
void		add_back(t_token **t, t_token *new_node);
void		display_tokens(t_token *t);
int			my_pwd(void);
void		execute_builtins(char *command);

#endif