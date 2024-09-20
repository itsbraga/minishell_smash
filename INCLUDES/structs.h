/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmateo <pmateo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 01:59:00 by art3mis           #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2024/09/20 19:35:01 by annabrag         ###   ########.fr       */
=======
/*   Updated: 2024/09/20 19:06:32 by pmateo           ###   ########.fr       */
>>>>>>> 5abb94ad707e158c85029dc47f2f59e712f46d05
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

typedef enum 	e_token_type
{
	COMMAND = 0,
	ARGUMENT,	// 1
	REDIR_IN,	// 2
	INFILE,		// 3
	HERE_DOC,	// 4
	LIMITER,	// 5
	TRUNC,		// 6
	APPEND,		// 7
	OUTFILE,	// 8
	WORD		// 9
}			 	t_token_type;

typedef struct s_parser
{
	char	*user_input;
	int		i;
	int		start;
	int		seg_count;
	char	**segment;
	bool	closed_quotes[2];
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
	struct s_main_lst	*main;
	int					i;
	int					start;
	int					token_count;
	char				**seg_elems;
	bool				closed_quotes[2];
}				t_token_parser;

typedef struct s_main_lst
{
	t_token_dblst		*tokens;
	char				*content;
	struct s_main_lst	*next;
}				t_main_lst;

typedef struct s_redir_lst
{
	t_token_type	type;
	char			*limiter;
	char			*infile;
	char			*outfile;
}				t_redir_lst;

typedef struct s_exec_lst
{
	t_redir_lst		*r;
	int				heredoc_nb;
	bool			absolute_path;
	char			**cmd;
}				t_exec_lst;

typedef struct s_exec_info
{
	int		cmd_count;
	int		executed_cmd;
	int		pipe_count;
	int		fd[2];
	int		old_read_fd;
	int		child_pid;
}				t_exec_info;

typedef struct s_env_lst
{
	char				*content;
	struct s_env_lst	*next;
}				t_env_lst;

typedef struct s_data
{
	char			*prompt;
	t_main_lst		*main;
	t_token_dblst	*token;
	t_exec_info		e_info;
	t_exec_lst		*exec;
	t_env_lst		*env;
	t_env_lst		*exp_env;
	int				last_exit_status;
}				t_data;

#endif