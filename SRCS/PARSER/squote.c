/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   squote.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: annabrag <annabrag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 15:52:48 by annabrag          #+#    #+#             */
/*   Updated: 2024/06/28 18:00:26 by annabrag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../INCLUDES/minishell.h"

/*	Enclosing characters in single-quotes ( '' ) shall preserve
	the literal value of each character within the single-quotes.
	A single-quote cannot occur within single-quotes.
	Example:
			elgato@42 $> '$HOME''
			elgato@42 $>
			elgato@42 $>
	It gives a dquote
*/
char	*squote(char **str)
{
	char	*token_c;
	int		i;

	i = 0;
	while (*str[i] != '\0' && *str[i] != '\'')
		i++;
	token_c = ft_substr(*str, 0, i);
	*str += i;
	return (token_c);
}
