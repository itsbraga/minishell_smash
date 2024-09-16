/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage_collector.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: annabrag <annabrag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 15:27:20 by pmateo            #+#    #+#             */
/*   Updated: 2024/09/16 20:01:17 by annabrag         ###   ########.fr       */
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

// FLAGS
#define CREATE 0
#define ADD 1
#define REMOVE -1
#define CLEAN_ALL -2

typedef struct s_gc_lst
{
	void			*ptr;
	struct s_gc_lst *next;
}				t_gc_lst;

int			remove_gc_node(t_gc_lst**yama, void *ptr);
void		add_gc_node(t_gc_lst **yama, t_gc_lst *node);
t_gc_lst	*last_gc_lst_node(t_gc_lst *yama);
void		*new_gc_node(void *ptr);
void		*yama(int flag, void *ptr, size_t size);

#endif