/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   custom.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmateo <pmateo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 16:15:15 by art3mis           #+#    #+#             */
/*   Updated: 2024/10/22 03:55:06 by pmateo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUSTOM_H
# define CUSTOM_H

# include "colors.h"

/******************************************************************************\
 * CUSTOM
\******************************************************************************/

# define BP BOLD PINK
# define BPP BOLD PURPLE

# define WELCOME_BANNER "\e[38;2;255;234;150m╔═════════════════════════════════════════════════════════════════════════╗\n║                                                                         ║\n║\t\t\e[31m░██████╗███╗░░░███╗░█████╗░░██████╗██╗░░██╗\t\t  \e[38;2;255;234;150m║\n║\t\t\e[31m██╔════╝████╗░████║██╔══██╗██╔════╝██║░░██║\t\t  \e[38;2;255;234;150m║\n║\t\t\e[31m╚█████╗░██╔████╔██║███████║╚█████╗░███████║\t\t  \e[38;2;255;234;150m║\n║\t\t\e[31m░╚═══██╗██║╚██╔╝██║██╔══██║░╚═══██╗██╔══██║\t\t  \e[38;2;255;234;150m║\n║\t\t\e[31m██████╔╝██║░╚═╝░██║██║░░██║██████╔╝██║░░██║\t\t  \e[38;2;255;234;150m║\n║\t\t\e[31m╚═════╝░╚═╝░░░░░╚═╝╚═╝░░╚═╝╚═════╝░╚═╝░░╚═╝\t\t  \e[38;2;255;234;150m║\n║                 \e[38;2;173;165;165m―――――――  Simple Mateo Anna SHell ―――――――                \e[38;2;255;234;150m║\n║                                                                         ║\n╚═════════════════════════════════════════════════════════════════════════╝\n\n\n"

# define LIM "=================================="
# define LIM2 "================================"
# define LIM3 "================================="

# define BYE_MSG "XOXO 💋"

/******************************************************************************\
 * DISPLAY FUNCTIONS
\******************************************************************************/

// display_2.c
void			display_exec_lst(t_exec_lst *e);
void			print_cmd(char **cmd);
void			print_tab(char **tab);
void			print_tab2(char **tab);
void			display_shell_info(void);

// display.c
void			display_export_env(t_env_lst *exp_env);
void			display_main_lst(t_main_lst *main);
void			display_token_dblst(t_token_dblst *t);
void			display_redir_lst(t_redir_lst *r);

// rainbow_txt.c
void			rainbow_txt(const char *str);
void			rainbow_txt_nonl(const char *str);
char			*rainbow_prompt(const char *str);

#endif