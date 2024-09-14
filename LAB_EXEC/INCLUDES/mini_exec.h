/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_exec.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmateo <pmateo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 21:02:51 by pmateo            #+#    #+#             */
/*   Updated: 2024/09/14 19:35:37 by pmateo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIEXEC_H
# define MINIEXEC_H

# include <stddef.h>
# include <stdio.h>
# include <unistd.h>
# include <sys/types.h>
# include <stdlib.h>
# include <stdbool.h>
# include <limits.h>
# include <errno.h>
# include <readline/readline.h>
# include "../../LIBFT/INCLUDES/libft.h"
# include "../../LIBFT/INCLUDES/ft_printf.h"
# include "../../LIBFT/INCLUDES/get_next_line_bonus.h"

# define FAILURE 1
# define SUCCESS 0

typedef struct s_env_lst
{
	char				*content;
	struct s_env_lst	*next;
}				t_env_lst;

typedef struct s_exec_lst
{
	char			*content;
	char			*here_doc;
	char			*limiter;
	char			*append;
	char			*red_in;
	char			*infile;
	char			*red_out;
	char			*outfile;
	bool			is_absolute_path;
	char			**cmd;
	struct s_exec_lst	*next;
}					t_exec_lst;

typedef struct s_exec_info
{
	int		cmd_count;
	int		pipe_count;
	int		fd[2];
	int		old_read_fd;
	int		child_pid;
}				t_exec_info;

t_env_lst	*env_new_var(char *content);
size_t		get_lst_size(t_exec_lst *e_lst);
int			create_env_list(t_env_lst **env, char **envp);
void		display_tokens(t_exec_lst *t);
void		display_tokens_with_infos(t_exec_lst *t);
void		build_lst(char *input, t_exec_lst **cmd);

#endif