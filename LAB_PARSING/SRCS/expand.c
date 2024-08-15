/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmateo <pmateo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 20:42:03 by pmateo            #+#    #+#             */
/*   Updated: 2024/08/15 18:39:21 by pmateo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../INCLUDES/mini_parsing.h"
// EXEMPLE : BLANC"$ROUGE"BLEU = BLANCBLEU
void	remove_var(char *str, char *var, size_t var_size)
{
	int	i;
	int	j;
	char *new_str;

	i = 0;
	j = (var - str) + 1;
	while ((str[j] >= 'A' && str[j] <= 'Z') || (str[j] >= '0' && str[j] <= '9'))
		j++;
		
}

void	add_var_value()
{
	
}

char	*expand(char *str, char *var, char **envp)
{
	int		i;
	int		j;
	char 	*to_find;
	char	*var_value;

	i = 0;
	to_find = take_var(str, var);
	var_value = search_var(to_find, envp);
	if (var_value == NULL)
		remove_var(str, var, ft_strlen(to_find) + 1);
	else
		add_var_value(str, var_value, ft_strlen(var_value));
	//
	
}

void	handle_expand(char *str, char **envp)
{
	int		i;
	bool 	closed;
	char	quote;

	i = 0;
	closed = true;
	quote = NULL;
	while (str[i])
	{
		if (str[i] == '\'' && quote != '"')
		{
			quote = '\'';
			closed = switch_bool(closed);
		}
		if (str[i] == '"' && quote != '\'')
		{
			quote = '"';
			closed = switch_bool(closed);
		}
		if (str[i] == '$' && (quote != '\'' && closed != false))
			str = expand(str, &str[i], envp);
		i++;
	}
}