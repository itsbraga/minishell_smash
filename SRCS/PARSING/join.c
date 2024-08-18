/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: art3mis <art3mis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 15:19:08 by annabrag          #+#    #+#             */
/*   Updated: 2024/08/18 22:38:53 by art3mis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"

static char	*__ft_strcat(char *dest, char *src)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (dest[i])
		i++;
	while (src[j])
	{
		dest[i] = src[j];
		j++;
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

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
		__ft_strcat(buffer, (char *)to_cat->next);
		to_cat = to_cat->next;
	}
	return (buffer);
}
