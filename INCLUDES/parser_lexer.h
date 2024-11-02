/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_lexer.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: art3mis <art3mis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 19:23:46 by art3mis           #+#    #+#             */
/*   Updated: 2024/11/02 01:17:58 by art3mis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_LEXER_H
# define PARSER_LEXER_H

# include "libraries.h"

/******************************************************************************\
 * LEXER
\******************************************************************************/

// parse_input_utils2.c
int				handle_bidirections(t_redir_parser *rp);
int				handle_spaced_sequence(t_redir_parser *rp, t_parser *p);
int				handle_redir_near_pipe(t_redir_parser *rp);

// parse_input_utils.c
// int				check_redir_order(t_parser *p);
int				check_redir_order(t_parser *p, t_redir_parser *rp);

// parse_input.c
int				parse_input(t_parser *p);

// create_main_lst.c
int				create_main_lst(t_data *d, char *input);

// parse_main.c
void			parse_segment(t_token_parser *p);

// tokenization.c
void			lst_tokenization(t_token_dblst *t);

// create_token_lst.c
int				create_token_dblst(t_data *d);

/******************************************************************************\
 * PARSER
\******************************************************************************/

// quotes_utils.c
bool			switch_bool(bool closed);
int				find_closing_quote(char *str, char quote);
bool			unclosed_quotes_return(bool closed[]);
char			*del_empty_quotes(char *str, int quote_idx);
char			*del_quote_pair(char *str, int first, int second);

// handle_quotes.c
bool			unclosed_quotes(char *str);
char			*empty_quotes(char *str);
char			*other_quotes(char *str);

// redir_lst_utils.c
t_redir_lst		*redir_in_n_infile(t_token_dblst *curr);
t_redir_lst		*redir_out_trunc_n_outfile(t_token_dblst *curr);
t_redir_lst		*redir_out_append_n_outfile(t_token_dblst *curr);
t_redir_lst		*heredoc_n_limiter(t_token_dblst *curr);

// create_redir_lst.c
int				create_redir_lst(t_data *d, t_exec_lst *existing_task);

// exec_lst_utils.c
void			init_ptrs(t_ptrs *p);
char			*token_cleanup(char *content);
int				cmd_token_count(t_token_dblst *t);

// create_exec_lst.c
int				create_exec_lst(t_data *d);

/******************************************************************************\
 * EXPANSION
\******************************************************************************/

// expand_exit_status.c
char			*handle_last_exit_status(char *str, char *var);

// expand_utils.c
size_t			len_to_equal(char *str);
char			*clean_translated_variable(char *str, char *var);
char			*take_var(char *str, char *var);
char			*search_var(char *to_find, t_env_lst *env);

// expand.c
char			*expand(t_data *d, char *str, bool in_heredoc);

#endif
