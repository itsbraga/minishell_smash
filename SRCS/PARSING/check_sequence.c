/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_sequence.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: annabrag <annabrag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 18:36:43 by art3mis           #+#    #+#             */
/*   Updated: 2024/10/09 21:31:17 by annabrag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_redir_sequence(char *content)
{
	int	i;

	i = 0;
	while (content[i] != '\0')
	{
		if (content[i] == '<' || ft_strcmp(content, "<<") == 0
			|| content[i] == '>' || ft_strcmp(content, ">>") == 0)
		{
			if (content[i + 1] == '\0' || content[i + 1] == '|'
				|| content[i + 2] == '|')
			{
				err_msg(NULL, "newline", 2);
				return (FAILURE);
			}
		}
		i++;
	}
	return (SUCCESS);
}
