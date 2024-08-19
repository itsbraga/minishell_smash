/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmateo <pmateo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 20:42:22 by pmateo            #+#    #+#             */
/*   Updated: 2024/08/19 19:45:32 by pmateo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../INCLUDES/mini_parsing.h"

// Si '' ou "" il faut supprimer les quotes
// Si single quote avec au moins un charactere a l'interieur = literal value except ENVVAR
// Si double quote avec au moins un charactere a l'interieur = literal value 


// Je parcours ma string
// Je tombe sur un quote 
//	Si je n'étais pas déjà dans des quotes alors closed = false pour que le quote soit marqué comme non fermé, mais si 
// 	Si j'étais déjà dans des quotes alors closed = true et le quote est marqué comme fermé
bool	unclosed_quotes_return(bool closed[])
{
	if (closed[0] == false || closed[1] == false)
		return (true);
	else
		return (false);
}

bool	unclosed_quotes(char *str)
{
	int	i;
	bool	closed[2];
	
	i = 0;
	closed[0] = true, closed[1] = true;
	while(str[i])
	{
		if (str[i] == '\'')
		{
			if (closed[0] == true && closed[1] == true)
				closed[0] = false;
			else
				closed[0] = true;
		}
		else if (str[i] == '"')
		{
			if (closed[1] == true && closed[0] == true)
				closed[1] = false;
			else
				closed[1] = true;
		}
		i++;
	}
	return (unclosed_quotes_return(closed));
}

char	*remove_empty_quotes(char *str, int quote_idx)
{
	int	i;
	int	j;
	char *new_str;

	i = 0;
	j = 0;
	printf("quoteidx = [%d]\n", quote_idx);
	new_str = malloc((ft_strlen(str) - 1) * (sizeof(char)));
	while (i != quote_idx)
	{
		new_str[i] = str[i];
		i++;
	}
	j = i + 2;
	while (str[j])
	{
		new_str[i] = str[j];
		i++;
		j++;
	}
	new_str[i] = '\0';
	printf("newstr = %s\n", new_str);
	free(str);
	return (new_str);
}
// EXEMPLE : he""he -> hehe
char	*empty_quotes(char *str)
{
	int		i;
	
	i = 0;
	while (str[i])
	{
		if ((str[i] == '"' && str[i + 1] == '"') || (str[i] == '\'' && str[i + 1] == '\''))
		{
			printf("emptyquote\n");
			str = remove_empty_quotes(str, i);
			i = 0;
		}
		else
			i++;
	}
	return (str);
}

// void	others_quotes(char *str)
// {
// 	int	i;
// 	int	j;

// 	i = 0;
// 	while (str[i])
// 	{
// 		if (str[i] == '\'')
// 		{
// 			j = i + 1;
// 			while (str[j] != '\'')
// 				j++;
// 			str = remove_filled_quotes_and_expand(str, &str[i], &str[j], '\'');
// 			i = j + 1;
// 		}
// 		else if (str[i] == '"')
// 		{
// 			j = i + 1;
// 			while (str[j] != '"')
// 				j++;
// 			str = remove_filled_quotes_and_expand(str, &str[i], &str[j], '"');
// 			i = j + 1;
// 		}
// 		i++;
// 	}
	
// }

bool	switch_bool(bool closed)
{
	if (closed == true)
		closed = false;
	else
		closed = true;
	return (closed);
}

char	*handle_quotes_and_expand(char *input, char **envp)
{
	(void)envp;
	if (unclosed_quotes(input) == true)
	{
		ft_putendl_fd("Unclosed quote !", 2);
		ft_putendl_fd("Aborting...", 2);
		exit(EXIT_FAILURE);
		// quote_exit();
	}
	printf("1\n");
	// SUPPRIME LES QUOTES VIDES INUTILES COMME BASH
	input = empty_quotes(input);
	printf("2\n");
	//VERIFIE SI $ ET SI OUI EXPAND OU NON SELON LES QUOTES
	//IL FAUDRAIT PEUT ETRE RE-UTILISE EMPTY_QUOTES DANS LE CAS OU UNE VARIABLE ENTOUREE
	// DE DOUBLE QUOTE SE RETROUVE SUPPRIME CAR VIDE
	// input = handle_expand(input, envp);
	//INTERPRETE LES QUOTES RESTANTS ET LES SUPPRIME
	// others_quotes(current->content);
	return (input);
}
