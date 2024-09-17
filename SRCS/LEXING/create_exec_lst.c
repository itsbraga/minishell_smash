/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_exec_lst.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: art3mis <art3mis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 17:44:18 by art3mis           #+#    #+#             */
/*   Updated: 2024/09/17 18:08:20 by art3mis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// typedef struct s_exec_lst
// {
// 	bool	here_doc;
// 	char	*limiter;
// 	bool	redir_in;
// 	char	*infile;
// 	size_t	redir_out;
// 	char	*outfile;
// 	bool	absolute_path;
// 	char	**cmd;
// }				t_exec_lst;

t_exec_lst  create_exec_lst(t_token_dblst **t);