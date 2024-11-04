/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   defines.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: art3mis <art3mis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 22:07:16 by art3mis           #+#    #+#             */
/*   Updated: 2024/11/04 03:03:47 by art3mis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEFINES_H
# define DEFINES_H
# define PATH_MAX 4096

# include "libraries.h"

/******************************************************************************\
 * FLAGS
\******************************************************************************/

// Yama
# define CREATE 0
# define CREATE_TAB 1
# define ADD 2
# define ADD_TAB 3
# define REMOVE -1
# define CLEAN_ALL -2
# define SEARCH -4

// General
# define NOT_A_BUILTIN 42
# define STOP_EXEC -42
# define CD_CASE 69

/******************************************************************************\
 * EXIT STATUS
\******************************************************************************/

# define SUCCESS 0
# define FAILURE 1

# define BAD_USAGE 2
# define CMD_CANNOT_EXEC 126
# define CMD_NOT_FOUND 127
# define OUT_OF_RANGE 255

# define CTRL_C 130 // 128 + signal 2 (SIGINT)
# define CTRL_BCKSLH 131 // 128 + signal 3 (SIGQUIT)

/******************************************************************************\
 * ERROR
\******************************************************************************/

# define ERR_PREFIX "\e[31m\e[1msmash: \e[0m"

// syntax error / user error
# define ERR_PIPE "syntax error near unexpected token `"
# define ERR_QUOTES "failed to handle quotes"
# define ERR_ENV_VAR "not a valid identifier"
# define ERR_ARG "too many arguments"
# define ERR_ARG_TYPE "numeric argument required"
# define ERR_BAD_FILE "No such file or directory"
# define ERR_NOT_DIR "Not a directory"

// creation
# define ERR_MALLOC "Memory allocation failed"

// exec
# define ERR_PWD "pwd: error retrieving current directory: "
# define ERR_GETCWD "getcwd: cannot access parent directories: "
# define ERR_CMD "command not found"
# define ERR_BAD_PERM "Permission denied"
# define ERR_IS_DIR "Is a directory"
# define ERR_NO_ENV "$PATH doesn't exist, please specify absolute path"
# define ERR_MAX_HD "maximum here-document count exceeded"

/******************************************************************************\
 * CUSTOM
\******************************************************************************/

/*# define BANNER "\e[38;2;255;234;150m╔═════════════════════════════════\
════════════════════════════════════════╗\n║                                   \
                                      ║\n║\t\t\e[31m░██████╗███╗░░░███╗░█████╗░\
░██████╗██╗░░██╗\t\t  \e[38;2;255;234;150m║\n║\t\t\e[31m██╔════╝████╗░████║██╔═\
═██╗██╔════╝██║░░██║\t\t  \e[38;2;255;234;150m║\n║\t\t\e[31m╚█████╗░██╔████╔██║\
███████║╚█████╗░███████║\t\t  \e[38;2;255;234;150m║\n║\t\t\e[31m░╚═══██╗██║╚██╔\
╝██║██╔══██║░╚═══██╗██╔══██║\t\t  \e[38;2;255;234;150m║\n║\t\t\e[31m██████╔╝██║\
░╚═╝░██║██║░░██║██████╔╝██║░░██║\t\t  \e[38;2;255;234;150m║\n║\t\t\e[31m╚═════╝\
░╚═╝░░░░░╚═╝╚═╝░░╚═╝╚═════╝░╚═╝░░╚═╝\t\t  \e[38;2;255;234;150m║\n║             \
 \e[38;2;211;211;211m―――――――  Simple Mateo Anna SHell ―――――――               \
 \e[38;2;255;234;150m║\n║                                                      \
                   ║\n╚════════════════════════════════════════════════════════\
═════════════════╝\n\n\n"*/

# define BANNER_PT1 "\e[38;2;255;234;150m╔═════════════════════════════════\
════════════════════════════════════════╗\n║                                   \
                                      ║\n║\t\t\e[31m░██████╗███╗░░░███╗░█████╗░\
░██████╗██╗░░██╗\t\t  \e[38;2;255;234;150m║\n║\t\t\e[31m██╔════╝████╗░████║██╔═\
═██╗██╔════╝██║░░██║\t\t  \e[38;2;255;234;150m║\n║\t\t\e[31m╚█████╗░██╔████╔██║\
███████║╚█████╗░███████║\t\t  \e[38;2;255;234;150m║\n║\t\t\e[31m░╚═══██╗██║╚██╔\
╝██║██╔══██║░╚═══██╗██╔══██║\t\t  \e[38;2;255;234;150m║\n║\t\t\e[31m██████╔╝██║\
░╚═╝░██║██║░░██║██████╔╝██║░░██║\t\t  \e[38;2;255;234;150m║\n║\t\t\e[31m╚═════╝\
░╚═╝░░░░░╚═╝╚═╝░░╚═╝╚═════╝░╚═╝░░╚═╝\t\t  \e[38;2;255;234;150m║\n║             \
   \e[38;2;211;211;211m―――――――"
# define CREATORS "  Simple Mateo Anna SHell "
# define BANNER_PT2 "\e[38;2;211;211;211m―――――――                 \
\e[38;2;255;234;150m║\n║                                                       \
                  ║\n╚═════════════════════════════════════════════════════════\
════════════════╝\n\n\n"

# define LIM "=================================="
# define LIM2 "================================"
# define LIM3 "================================="

#endif