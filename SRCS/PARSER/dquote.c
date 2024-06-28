/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dquote.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: annabrag <annabrag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 19:51:15 by annabrag          #+#    #+#             */
/*   Updated: 2024/06/28 16:44:54 by annabrag         ###   ########.fr       */
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
	char	*token_c;
	int		i;

	i = 0;
	while (*str[i] != '\0' && (*str[i] != '"' || *str[i] != '$'))
		i++;
	token_c = ft_substr(*str, 0, i);
	*str += i;
	return (token_c);
}
