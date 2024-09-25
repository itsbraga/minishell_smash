/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage_collector.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: annabrag <annabrag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 15:27:20 by pmateo            #+#    #+#             */
/*   Updated: 2024/09/25 19:44:37 by annabrag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef	GARBAGE_COLLECTOR_H
# define GARBAGE_COLLECTOR_H

# include <stddef.h>
# include <stdio.h>
# include <unistd.h>
# include <sys/types.h>
# include <stdbool.h>
# include <stdlib.h>

/******************************************************************************\
 * FLAGS
\******************************************************************************/

# define CREATE 0
# define CREATE_TAB 1
# define ADD 2
# define ADD_TAB 3
# define REMOVE -1
# define CLEAN_ALL -2

/******************************************************************************\
 * YAMA'S STRUCT
\******************************************************************************/

typedef struct s_gc_lst
{
	void			*ptr;
	bool			is_tab;
	struct s_gc_lst *next;
}				t_gc_lst;

/******************************************************************************\
 * FUNCTIONS
\******************************************************************************/

void		free_tab(char **tab);
int			remove_gc_node(t_gc_lst**yama, void *ptr);
void		add_gc_node(t_gc_lst **yama, t_gc_lst *node);
t_gc_lst	*last_gc_lst_node(t_gc_lst *yama);
void		*new_gc_node(void *ptr, bool is_tab);
void		*yama(int flag, void *ptr, size_t size);

#endif