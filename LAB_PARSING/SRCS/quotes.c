/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmateo <pmateo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 20:42:22 by pmateo            #+#    #+#             */
/*   Updated: 2024/07/08 01:45:00 by pmateo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../INCLUDES/mini_parsing.h"

// Si '' ou "" il me faut supprimer les quotes
// Si single quote avec au moins un charactere a l'interieur = literal value except ENVVAR
// Si double quote avec au moins un charactere a l'interieur = literal value

// Cette fonction n'est pas suffisante
// bool	unclosed_quotes(char *str)
// {
// 	int 	i;
// 	int		nb_squote;
// 	int		nb_dquote;
	
// 	i = 0;
// 	nb_squote = 0;
// 	nb_dquote = 0;
// 	while (str[i])
// 	{
// 		if (str[i] == '\'')
// 			nb_squote++;
// 		else if (str[i] == '"')
// 			nb_dquote++;
// 		i++;
// 	}
// 	if (nb_squote % 2 == 1 || nb_dquote % 2 == 1)
// 		return (true);
//	else
// 		return (false);
// }

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
	free(str);
	return (new_str);
}


void	empty_quotes(t_token *current)
{
	char *str;
	int		i;
	
	str = current->content;
	i = 0;
	while (str[i])
	{
		if ((str[i] == '"' && str[i + 1] == '"') || (str[i] == '\'' && str[i + 1] == '\''))
		{
			current->content = remove_empty_quotes(str, i);
			i = 0;
			str = current->content;
		}
		else
			i++;
	}
}

void	handle_quotes(t_token **tok)
{
	size_t	size_list;
	t_token *current;
	
	size_list = get_tlist_size(tok);
	current = *tok;
	while (size_list)
	{
		if (unclosed_quotes(current->content) == true)
		{
			ft_putendl_fd("Unclosed quote ! Aborting...", 2);
			exit(EXIT_FAILURE);
			// quote_exit();
		}
		empty_quotes(current);
		// others_quotes(current);
		current = current->next;
		size_list--;
	}
}