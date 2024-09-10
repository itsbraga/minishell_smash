/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: art3mis <art3mis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 01:59:00 by art3mis           #+#    #+#             */
/*   Updated: 2024/09/10 17:37:50 by art3mis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

typedef enum 	e_token_type
{
	COMMAND = 0,
	ARGUMENT,
	BUILT_IN,
	SEPARATOR,
	REDIR_IN, // ou STDIN_FILE ou OPEN_FILE
	INFILE,
	REDIR_OUT, // ou TRUNC ou CREAT_FILE
	OUTFILE,
	APPEND,
	HEREDOC,
	LIMITER
}			 	t_token_type;

typedef struct s_parser
{
	char	*user_input;
	int		i;
	int		start;
	int		token_count;
	char	**elems;
	bool	closed_quotes[2];
}				t_parser;

typedef struct s_token
{
	t_token_type	type;
	char			*content;
	struct s_token	*next;
}				t_token;

typedef struct s_sub_lst
{
	t_token				*head_token;	// Liste de tokens pour cette commande
	struct s_sub_lst	*next;			// Lien vers la prochaine liste de tokens (prochaine commande)
}				t_sub_lst;

typedef struct s_classifier
{
	t_token		*token_lst;
	t_token		*token;
	char		**elems;
	size_t		i;
}				t_classifier;

typedef struct s_main_lst
{
	char				*content;
	struct s_main_lst	*next;
}				t_main_lst;

typedef struct s_env
{
	char			*content;
	struct s_env	*next;
}				t_env;

typedef struct s_global
{
	char		*prompt;
	t_main_lst	*main;
	t_token		*token;
	t_env		*env;
	t_env		*exp_env;
	int			last_exit_status;
}				t_global;

// typedef struct s_command
// {
// 	char				*cmd;
// 	char				**args;
// 	struct s_command	*next;
// }				t_command;

#endif