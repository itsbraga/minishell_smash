/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   defines.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: art3mis <art3mis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 17:49:02 by annabrag          #+#    #+#             */
/*   Updated: 2024/09/24 20:42:40 by art3mis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEFINES_H
# define DEFINES_H

# include "colors.h"

# ifndef PATH_MAX
#  define PATH_MAX 4096
# endif

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

# define ERR_PREFIX (BOLD RED "smash: " RESET)
# define ERR_NEAR_PIPE "syntax error near unexpected token `|'"
# define ERR_MALLOC "cannot allocate memory"
# define ERR_QUOTES "failed to handle quotes"
# define ERR_BAD_FILE "No such file or directory"
# define ERR_CMD "command not found"

/******************************************************************************\
 * CUSTOM
\******************************************************************************/

# define WELCOME_BANNER "\e[93m╔═════════════════════════════════════════════════════════════════════════╗\n║                                                                         ║\n║\t\t\e[91m░██████╗███╗░░░███╗░█████╗░░██████╗██╗░░██╗\t\t  \e[93m║\n║\t\t\e[91m██╔════╝████╗░████║██╔══██╗██╔════╝██║░░██║\t\t  \e[93m║\n║\t\t\e[91m╚█████╗░██╔████╔██║███████║╚█████╗░███████║\t\t  \e[93m║\n║\t\t\e[91m░╚═══██╗██║╚██╔╝██║██╔══██║░╚═══██╗██╔══██║\t\t  \e[93m║\n║\t\t\e[91m██████╔╝██║░╚═╝░██║██║░░██║██████╔╝██║░░██║\t\t  \e[93m║\n║\t\t\e[91m╚═════╝░╚═╝░░░░░╚═╝╚═╝░░╚═╝╚═════╝░╚═╝░░╚═╝\t\t  \e[93m║\n║                                                                         ║\n╚═════════════════════════════════════════════════════════════════════════╝\n\n\n"

# define BYE_MSG "Bye le sangreee"

#endif