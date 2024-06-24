/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_exec.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmateo <pmateo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 21:02:51 by pmateo            #+#    #+#             */
/*   Updated: 2024/06/24 02:40:29 by pmateo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIEXEC_H
# define MINIEXEC_H

# include <stddef.h>
# include <stdio.h>
# include <unistd.h>
# include <sys/types.h>
# include <stdlib.h>
# include <limits.h>
# include <errno.h>
# include "../LIBFT/INCLUDES/libft.h"
# include "../LIBFT/INCLUDES/ft_printf.h"
# include "../LIBFT/INCLUDES/get_next_line_bonus.h"

# define MALLOC_ERR -1
# define PARSING_ERR -2
# define LEXER_ERR -3
# define EXP_ERR -4
# define EXEC_ERR -5
# define TRUE 1
# define FALSE 0

typedef struct s_tlist
{
	int             pos;
    char			*content;
	struct s_plist	*next;
}					t_tlist;

typedef struct s_exec
{
    char *input;
	char **envp;
}   t_exec;

void    init_e(t_exec *e);

#endif