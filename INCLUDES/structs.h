/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: annabrag <annabrag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 01:59:00 by art3mis           #+#    #+#             */
/*   Updated: 2024/09/11 20:36:06 by annabrag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

typedef enum 	e_token_type
{
	COMMAND = 0,
	ARGUMENT,
	BUILT_IN,
	REDIR_IN,
	INFILE,
	HERE_DOC,
	LIMITER,
	TRUNC,
	APPEND,
	OUTFILE
}			 	t_token_type;

typedef struct s_parser
{
	char	*user_input;
	int		i;
	int		start;
	int		token_count;
	char	**segment;
	bool	closed_quotes[2];
}				t_parser;

typedef struct s_exec_lst
{
	bool	here_doc;
	char	*limiter;
	bool	redir_in;
	char	*infile;
	int		redir_out;
	char	*outfile;
	bool	absolute_path;
	char	**cmd;
}				t_exec_lst;

typedef struct s_exec_info
{
	int		cmd_count;
	int		pipe_count;
}				t_exec_info;

typedef struct s_token_lst
{
	t_token_type		type;
	char				*content;
	struct s_token_lst	*next;
}				t_token_lst;

typedef struct s_classifier
{
	t_token_lst		*head_token_lst;
	t_token_lst		*token;
	char			**seg_elems;
	size_t			i;
}				t_classifier;

typedef struct s_main_lst
{
	char				*content;
	struct s_main_lst	*next;
}				t_main_lst;

typedef struct s_env_lst
{
	char				*content;
	struct s_env_lst	*next;
}				t_env_lst;

typedef struct s_global
{
	char			*prompt;
	t_exec_info		info;
	t_main_lst		*main;
	t_token_lst		*token;
	t_env_lst		*env;
	t_env_lst		*exp_env;
	int				last_exit_status;
}				t_global;

#endif