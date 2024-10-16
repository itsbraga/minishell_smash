/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: art3mis <art3mis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 22:07:16 by art3mis           #+#    #+#             */
/*   Updated: 2024/10/16 16:17:29 by art3mis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEFINES_H
# define DEFINES_H

# include "colors.h"

/******************************************************************************\
 * GENERAL
\******************************************************************************/

# define PATH_MAX 4096
# define IS_REDIR(t) ((t == REDIR_IN) || (t == HERE_DOC) \
						|| (t == REDIR_OUT_TRUNC) || (t == REDIR_OUT_APPEND))
# define CLEAR_LINE "\33[2K\r"

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

#endif