/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dquote.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: annabrag <annabrag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 19:51:15 by annabrag          #+#    #+#             */
/*   Updated: 2024/06/28 19:51:13 by annabrag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../INCLUDES/minishell.h"

/*
	Enclosing characters in double-quotes ( "" ) shall preserve
	the literal value of all characters within the double-quotes,
	with the exception of the characters dollar sign, backquote,
	and backslash
*/
char	*dquote(char **str)
{
	char	*t_content;
	int		i;

	i = 0;
	while (*str[i] != '\0' && (*str[i] != '"' || *str[i] != '$'))
		i++;
	t_content = ft_substr(*str, 0, i);
	*str += i;
	return (t_content);
}

bool	add_dquote_content(char **str, t_token **t)
{
	char	*content;
	t_token	*new_token;
	
	content = NULL;
	if (**str == '"')
		content = dquote(str);
	if (content != NULL)
		new_token = new_node(content);
	if (!content || !new_token)
	{
		delone_token(new_token);
		return (false);
	}
	add_back(t, new_token);
	return (true);
}
