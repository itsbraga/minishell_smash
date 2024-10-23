/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing-lexing.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: annabrag <annabrag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 19:23:46 by art3mis           #+#    #+#             */
/*   Updated: 2024/10/23 14:53:40 by annabrag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_LEXING_H
# define PARSING_LEXING_H

# include "libraries.h"

/******************************************************************************\
 * LEXING
\******************************************************************************/

// check_input.c
void			parse_input(t_parser *p);

// create_main_lst.c
int				create_main_lst(t_data *d, char *user_input);

// check_main.c
void			parse_segment(t_token_parser *p);

// tokenization.c
void			lst_tokenization(t_token_dblst *t);

// create_token_lst.c
int				create_token_dblst(t_data *d);

/******************************************************************************\
 * PARSING
\******************************************************************************/

// check_sequence.c
int				check_redir_sequence(char *content, t_token_parser *p);

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
t_redir_lst		*redir_in_n_infile(t_data *d);
t_redir_lst		*redir_out_trunc_n_outfile(t_data *d);
t_redir_lst		*redir_out_append_n_outfile(t_data *d);
t_redir_lst		*heredoc_n_limiter(t_data *d);

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

// expand_utils.c
size_t			len_to_equal(char *str);
char			*clean_translated_variable(char *str, char *var);
char			*take_var(char *str, char *var);
char			*search_var(char *to_find, t_env_lst *env);

// expand.c
char			*expand(t_data *d, char *str, bool in_heredoc);

#endif
