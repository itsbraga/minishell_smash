/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: art3mis <art3mis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 01:59:00 by art3mis           #+#    #+#             */
/*   Updated: 2024/11/04 02:42:01 by art3mis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

# include "libraries.h"

/******************************************************************************\
 * PARSING including LEXING
\******************************************************************************/

typedef enum e_mode
{
	ADD,
	GET
}			t_mode;

typedef enum e_token_type
{
	UNKNOWN = -1,
	COMMAND,
	WORD,
	REDIR_IN,
	INFILE,
	HERE_DOC,
	LIMITER,
	REDIR_OUT_TRUNC,
	REDIR_OUT_APPEND,
	OUTFILE
}			t_token_type;

typedef struct s_redir_parser
{
	char	curr_char;
	int		rcount;
	int		rcount2;
	char	next_char;
	int		space;
	int		count_next;
	bool	is_db_redir;
}				t_redir_parser;

typedef struct s_parser
{
	char			*input;
	char			*tmp;
	int				i;
	int				start;
	int				seg_count;
	char			**segment;
	bool			closed_quotes[2];
}				t_parser;

typedef struct s_token_dblst
{
	t_token_type			type;
	char					*content;
	struct s_token_dblst	*prev;
	struct s_token_dblst	*next;
}				t_token_dblst;

typedef struct s_token_parser
{
	char	*main_content;
	int		i;
	int		start;
	int		token_count;
	char	**seg_elems;
	bool	closed_quotes[2];
}				t_token_parser;

typedef struct s_main_lst
{
	char				*content;
	struct s_main_lst	*next;
}				t_main_lst;

/******************************************************************************\
 * BEFORE EXECUTION
\******************************************************************************/

typedef struct s_redir_lst
{
	t_token_type		type;
	char				*limiter;
	char				*infile;
	char				*outfile;
	struct s_redir_lst	*next;
}				t_redir_lst;

typedef struct s_ptrs
{
	struct s_exec_lst	*new_task;
	int					i;
}				t_ptrs;

typedef struct s_exec_lst
{
	t_redir_lst			*redir;
	int					heredoc_nb;
	int					latest_hd;
	bool				is_given_path;
	char				*bin_path;
	char				**cmd;
	struct s_exec_lst	*next;
}				t_exec_lst;

typedef struct s_exec_info
{
	int		cmd_count;
	int		executed_cmd;
	int		pipe_count;
	int		fd[2];
	int		hd_fd[2];
	int		all_cmd_heredoc_nb;
	int		old_read_fd;
	int		child_pid;
}				t_exec_info;

/******************************************************************************\
 * YAMA: Garbage collector
\******************************************************************************/

typedef struct s_gc_lst
{
	void			*ptr;
	bool			is_tab;
	struct s_gc_lst	*next;
}				t_gc_lst;

/******************************************************************************\
 * GENERAL
\******************************************************************************/

typedef struct s_env_lst
{
	char				*content;
	struct s_env_lst	*next;
}				t_env_lst;

typedef struct s_prompt
{
	char	*username;
	// char	*rainbow_user;
	char	*user;
	char	*extracted;
	char	*home_path;
	char	*home_pos;
	char	*custom_cwd;
	char	*part1;
	char	*part2;
	char	*part3;
}				t_prompt;

typedef struct s_data
{
	char			*prompt;
	int				fd_stdin_backup;
	t_main_lst		*main;
	t_token_dblst	*token;
	t_exec_info		*info;
	t_exec_lst		*exec;
	t_env_lst		*env;
	t_env_lst		*exp_env;
}				t_data;

#endif