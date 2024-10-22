/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmateo <pmateo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 22:07:16 by art3mis           #+#    #+#             */
/*   Updated: 2024/10/22 22:25:33 by pmateo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HELPERS_H
# define HELPERS_H

# include "colors.h"

/******************************************************************************\
 * GENERAL
\******************************************************************************/

# define _XOPEN_SOURCE 700
# define PATH_MAX 4096
# define IS_REDIR(t) ((t == REDIR_IN) || (t == HERE_DOC) \
						|| (t == REDIR_OUT_TRUNC) || (t == REDIR_OUT_APPEND))

/******************************************************************************\
 * YAMA'S FLAGS
\******************************************************************************/

# define CREATE 0
# define CREATE_TAB 1
# define ADD 2
# define ADD_TAB 3
# define REMOVE -1
# define CLEAN_ALL -2
# define SEARCH -4

/******************************************************************************\
 * EXIT STATUS
\******************************************************************************/

# define SUCCESS 0
# define FAILURE 1
# define MISUSE_CMD 2
# define CMD_CANNOT_EXEC 126
# define CMD_NOT_FOUND 127
# define CTRL_C_EXIT 130 // 128 + signal 2 (SIGINT)
# define KILL_EXIT 143 // 128 + signal 15 (SIGTERM)
# define OUT_OF_RANGE 255

/******************************************************************************\
 * ERROR
\******************************************************************************/

# define ERR_PREFIX (BOLD RED "smash: " R)
# define ERR_PIPE "syntax error near unexpected token `"
# define ERR_MALLOC "cannot allocate memory"
# define ERR_QUOTES "failed to handle quotes"
# define ERR_ARG "too many arguments"
# define ERR_ARG_TYPE "numeric argument required"
# define ERR_BAD_FILE "No such file or directory"
# define ERR_CMD "command not found"
# define ERR_NO_ENV "$PATH doesn't exist, please specify absolute path"
# define ERR_BAD_PERM "Permission denied"
# define ERR_MAX_HD "maximum here-document count exceeded"

#endif