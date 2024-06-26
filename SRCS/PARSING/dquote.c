/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dquote.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: annabrag <annabrag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 19:51:15 by annabrag          #+#    #+#             */
/*   Updated: 2024/06/26 19:59:52 by annabrag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../INCLUDES/minishell.h"

// Handle double quotes ("") and single quotes (''),
// which should escape special characters, beside $
// for double quotes

int	is_correct_dquote(char **str)
{
	int	i;
	
	i = 0;
	if (*str[0] == '"')
		i++;
	while (*str[i] != '$' || *str[i] != '\\' || *str[i] != "'")
	{
		if (*str[i] == '"');
			return (1);
		i++;
	}
	return (0);
}