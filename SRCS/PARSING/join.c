/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: annabrag <annabrag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 15:19:08 by annabrag          #+#    #+#             */
/*   Updated: 2024/08/16 14:23:29 by annabrag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*ft_strcat(char *dest, char *src)
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
		ft_strcat(buffer, (char *)to_cat->content);
		to_cat = to_cat->next;
	}
	return (buffer);
}