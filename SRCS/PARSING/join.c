/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: art3mis <art3mis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 15:19:08 by annabrag          #+#    #+#             */
/*   Updated: 2024/08/18 19:40:00 by art3mis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// recoder strcat
char	*cat_tcontent(t_token *to_cat)
{
	t_token	*tmp;
	char	*buffer;
	int		to_malloc;
	
	tmp = to_cat;
	buffer = NULL;
	to_malloc = 0;
	while (tmp != NULL && tmp->content != NULL)
	{
		to_malloc += ft_strlen((char *)tmp->content);
		tmp = tmp->next;	
	}
	buffer = ft_calloc((to_malloc + 1), sizeof(char));
	if (!buffer)
		return (NULL);
	while (to_cat != NULL && to_cat->content != NULL)
	{
		strcat(buffer, (char *)to_cat->content);
		to_cat = to_cat->next;
	}
	return (buffer);
}
