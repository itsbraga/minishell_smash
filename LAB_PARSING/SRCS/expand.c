/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmateo <pmateo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 20:42:03 by pmateo            #+#    #+#             */
/*   Updated: 2024/08/16 19:39:32 by pmateo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../INCLUDES/mini_parsing.h"
// EXEMPLE : BLANC"$ROUGE"BLEU = BLANC""BLEU
char	*remove_var(char *str, char *var, size_t var_size)
{
	// IDX[0] = debut str ; IDX[1] = CHAR AVANT $ ; IDX[2] = CHAR APRES VAR 
	int	idx[3];
	char *new_str;

	idx[0] = 0;
	idx[1] = (var - str);
	idx[2] = (var - str) + 1;
	new_str = malloc((ft_strlen(str) - var_size + 1) * (sizeof(char)));
	printf("4.1\n");
	while ((str[idx[2]] >= 'A' && str[idx[2]] <= 'Z') || (str[idx[2]] >= '0' && str[idx[2]] <= '9') || (str[idx[2]] == '_'))
		idx[2]++;
	printf("4.2\n");
	while (idx[0] != idx[1])
	{
		new_str[idx[0]] = str[idx[0]];
		idx[0]++;
	}
	printf("4.3\n");
	while (str[idx[2]])
	{
		new_str[idx[0]] = str[idx[2]];
		idx[0]++;
		idx[2]++;	
	}
	printf("4.4\n");
	free(str);
	return (new_str);
}
//EXEMPLE : gg"$USER"wp = gg"pmateo"wp
char	*add_var_value(char *str, char *var, char *var_value, size_t vv_size)
{
	int idx[3];
	char *new_str;

	idx[0] = 0;
	idx[1] = (var - str);
	idx[2] = (var - str) + 1;
	new_str = malloc((ft_strlen(str) - vv_size + 1) * (sizeof(char)));
	printf("4.5\n");
	while ((str[idx[2]] >= 'A' && str[idx[2]] <= 'Z') 
				|| (str[idx[2]] >= '0' && str[idx[2]] <= '9') 
				|| str[idx[2]] == '_')
		idx[2]++;
	while (idx[0] != idx[1])
	{
		new_str[idx[0]] = str[idx[0]];
		idx[0]++;
	}
	printf("4.6\n");
	printf("idx[1] = %d, idx[2] = %d, vv_size = %zu, value = %s\n", idx[1], idx[2], vv_size, var_value);
	while (*var_value != '\0')
	{
		new_str[idx[0]] = *var_value;
		idx[0]++;
		var_value++;
		printf("while\n");
	}
	printf("4.7\n");
	while (str[idx[2]])
	{
		new_str[idx[0]] = str[idx[2]];
		idx[0]++;
		idx[2]++;
		printf("while\n");
	}
	free(str);
	return (new_str);
}

char	*expand(char *str, char *var, char **envp)
{
	char 	*to_find;
	char	*var_value;

	printf("3\n");
	to_find = take_var(str, var);
	// if (*to_find == '?')
	// 	var_value = last_exit_code();
	// else
	printf("to_find = %s\n", to_find);
	var_value = search_var(to_find, envp);
	printf("4\n");
	printf("vv = %s\n", var_value);
	//SUPPRESSION DE LA VARIABLE SI INTROUVABLE
	//AJOUT DE LA VALEUR SINON
	if (var_value == NULL)
		str = remove_var(str, var, ft_strlen(to_find) + 1);
	else
		str = add_var_value(str, var, var_value, ft_strlen(var_value));
	printf("5\n");
	return (str);
}

char *handle_expand(char *str, char **envp)
{
	//EXEMPLE : "'$USER'" = "'pmateo'" | '"$USER"' = '"$USER"'
	int		i;
	bool 	closed;
	char	quote;

	i = 0;
	closed = true;
	quote = 0;
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
		if (str[i] == '$' && (quote != '\'' && closed == false))
			str = expand(str, &str[i], envp);
		i++;
	}
	return (str);
}