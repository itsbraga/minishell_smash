/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmateo <pmateo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 15:27:20 by pmateo            #+#    #+#             */
/*   Updated: 2024/10/21 20:00:10 by pmateo           ###   ########.fr       */
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
# define CREATE 0
# define CREATE_TAB 1
# define ADD 2
# define ADD_TAB 3
# define REMOVE -1
# define CLEAN_ALL -2
# define PRINT_LST -3

# define SUCCESS 0
# define FAILURE 1
# define ERR_MALLOC "cannot allocate memory"
# define ERR_PREFIX "smash: "
# define ERR_PIPE "syntax error near unexpected token `"

typedef struct s_gc_lst
{
	void			*ptr;
	bool			is_tab;
	struct s_gc_lst *next;
}				t_gc_lst;

int			free_gc_tab(t_gc_lst **yama, char **tab);
int			handle_remove(t_gc_lst **yama, void *ptr);
int			remove_gc_node(t_gc_lst **yama, void *ptr);
void		add_gc_node(t_gc_lst **yama, t_gc_lst *node);
t_gc_lst	*last_gc_lst_node(t_gc_lst *yama);
void		*new_gc_node(void *ptr, bool is_tab);
void		*yama(int flag, void *ptr, size_t size);
char		**ft_split(char const *s, char c);
void		*ft_memcpy(void *dest, const void *src, size_t n);
size_t		ft_strlen(const char *str);
size_t		ft_strlcpy(char *dest, const char *src, size_t size);
char		*ft_strjoin(char const *s1, char const *s2);
char		*ft_strdup(const char *s1);
void		secure_malloc(void *to_secure);
void		err_msg(char *detail, char *reason, int quotes);
void		clean_exit_shell(int err_status);

#endif