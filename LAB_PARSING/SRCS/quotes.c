/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmateo <pmateo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 20:42:22 by pmateo            #+#    #+#             */
/*   Updated: 2024/08/22 19:05:07 by pmateo           ###   ########.fr       */
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
	while(str[i] != '\0')
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
	// printf("quoteidx = [%d]\n", quote_idx);
	new_str = malloc((ft_strlen(str) - 1) * (sizeof(char)));
	while (i != quote_idx)
	{
		new_str[i] = str[i];
		i++;
	}
	j = i + 2;
	while (str[j] != '\0')
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
// EXEMPLE : """'''"""''$USER''"""'''""" = "'''"$USER"'''"
char	*empty_quotes(char *str)
{
	int		i;
	bool	closed[2];

	i = 0;
	closed[0] = true;
	closed[1] = true;
	printf("5\n");
	while (str[i] != '\0')
	{
		if ((str[i] == '"' && str[i + 1] == '"') && (closed[1] != false && closed[0] != false))
		{
			str = remove_empty_quotes(str, i);
			i = 0;
			closed[0] = true;
			closed[1] = true;
		}
		else if ((str[i] == '\'' && str[i + 1] == '\'') && (closed[0] != false && closed[1] != false))
		{
			str = remove_empty_quotes(str, i);
			i = 0;
			closed[0] = true;
			closed[1] = true;
		}
			
		if (str[i] == '"' && closed[1] != false)
			closed[0] = switch_bool(closed[0]);
		else if (str[i] == '\'' && closed[0] != false)
			closed[1] = switch_bool(closed[1]);
		i++;
	}
	return (str);
}
char	*remove_one_quote(char *str, int pos)
{
	
}	

char	*remove_others_quotes(char *str, int pos[2])
{
	str = remove_one_quote(str, pos[0]);
	str = remove_one_quote(str, pos[1]);
	return (str);
}

// IL VA ME FALLOIR UNE FONCTION QUI RECUPERE LA POSITION DE DEUX QUOTE ET QUI
// APPEL DEUX FOIS UNE FONCTION QUI SUPPRIME UN SEUL QUOTE PAR SA POSITION
// IL ME FAUDRA SUREMENT AUSSI UN COMPTEUR DE CARACTERE ME PERMETTANT D'IGNORER LES
// QUOTES A NE PAS SUPPRIMER ET A SUIVRE L'AVANCEE DANS LA STRING 
// EXEMPLE : "''""''" = ''''
char	*others_quotes(char *str)
{
	int	i[2];
	int meter;
	bool	closed[2];

	i[0] = 0;
	meter = 0;
	closed[0] = true;
	closed[1] = true;
	while (str[i[0]] != '\0')
	{
		if (str[i[0]] == '"')
		{
			i[1] = (i[0] + 1);
			while (str[i[1]] != '"')
				i[0]++;
			str = remove_others_quotes(str, i);
			meter = i[1];
		}
		else if (str[i[0]] == '\'')
		{
			i[1] = (i[0] + 1);
			while (str[i[1]] != '\'')
				i[0]++;
			str = remove_others_quotes(str, i);
			meter = i[1];
		}
		i[0]++;
	}
	return (str);
}

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
	input = handle_expand(input, envp);
	input = empty_quotes(input);
	printf("3\n");
	//INTERPRETE LES QUOTES RESTANTS ET LES SUPPRIME
	input = others_quotes(input);
	return (input);
}
