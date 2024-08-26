/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   squote.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: annabrag <annabrag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 15:52:48 by annabrag          #+#    #+#             */
/*   Updated: 2024/08/26 16:59:23 by annabrag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*	Enclosing characters in single-quotes ( '' ) shall preserve
	the literal value of each character within the single-quotes.
	A single-quote cannot occur within single-quotes.
	Example:
			elgato@42 $> '$HOME''
			elgato@42 $>
			elgato@42 $>
	It gives a dbquote
*/

// ajouter un flag pour indiquer s'il y a plus de deux single quotes
char	*squote(char **str)
{
	char	*t_content;
	int		i;
//	int		has_quote;

	t_content = NULL;
	i = 0;
//	has_quote = 0;
	while (*str[i] != '\0' && *str[i] != '\'')
		i++;
	t_content = ft_substr(*str, 0, i);
	*str += i;
	return (t_content);
}

int	add_squote_content(char **str, t_token **t)
{
	char	*content;
	t_token	*new_elem;
	
	content = NULL;
	if (**str == '\'')
		content = squote(str);
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
