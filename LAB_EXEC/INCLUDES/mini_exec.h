/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_exec.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmateo <pmateo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 21:02:51 by pmateo            #+#    #+#             */
/*   Updated: 2024/09/03 16:42:12 by pmateo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIEXEC_H
# define MINIEXEC_H

# include <stddef.h>
# include <stdio.h>
# include <unistd.h>
# include <sys/types.h>
# include <stdlib.h>
# include <stdbool.h>
# include <limits.h>
# include <errno.h>
# include <readline/readline.h>
# include "../../LIBFT/INCLUDES/libft.h"
# include "../../LIBFT/INCLUDES/ft_printf.h"
# include "../../LIBFT/INCLUDES/get_next_line_bonus.h"

# define FAILURE 1
# define SUCCESS 0

typedef struct s_tok
{
    char			*content;
	char			*here_doc;
	char			*limiter;
	char			*append;
	char			*red_in;
	char			*infile;
	char			*red_out;
	char			*outfile;
	char			**cmd;
	struct s_tok	*next;
}					t_tok;

void	display_tokens(t_tok *t);
void	build_lst(char *input, t_tok **cmd);

#endif