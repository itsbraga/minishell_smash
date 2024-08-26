/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dbquote.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: annabrag <annabrag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 19:51:15 by annabrag          #+#    #+#             */
/*   Updated: 2024/08/13 15:01:49 by annabrag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
	Enclosing characters in double-quotes ( "" ) shall preserve
	the literal value of all characters within the double-quotes,
	with the exception of the characters dollar sign, backquote,
	and backslash
*/
char	*dbquote(char **str)
{
	char	*t_content;
	int		i;
	
	t_content = NULL;
	i = 0;
	while (*str[i] != '\0' && (*str[i] != '"' || *str[i] != '$'))
		i++;
	t_content = ft_substr(*str, 0, i);
	*str += i;
	return (t_content);
}

int	add_dbquote_content(char **str, t_token **t)
{
	char	*content;
	t_token	*new_elem;
	
	content = NULL;
	if (**str == '"')
		content = dbquote(str);
	// else if (**str == '$')
	// 	content = dollar();
	if (content != NULL)
		new_elem = new_node(content);
	if (!content || !new_elem)
	{
		lstclear_tokens(t);
		return (FAILURE);
	}
	add_back(t, new_elem);
	return (SUCCESS);
}
