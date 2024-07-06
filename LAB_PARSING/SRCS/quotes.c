/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmateo <pmateo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 20:42:22 by pmateo            #+#    #+#             */
/*   Updated: 2024/07/06 17:08:48 by pmateo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../INCLUDES/mini_parsing.h"

// Si '' ou "" il me faut supprimer les quotes
// Si single quote avec au moins un charactere a l'interieur = literal value except ENVVAR
// Si double quote avec au moins un charactere a l'interieur = literal value


bool	unclosed_quotes(char *str)
{
	int 	i;
	int		nb_squote;
	int		nb_dquote;
	
	i = 0;
	nb_squote = 0;
	nb_dquote = 0;
	while (str[i])
	{
		if (str[i] == '\'')
			nb_squote++;
		else if (str[i] == '"')
			nb_dquote++;
		i++;
	}
	if (nb_squote % 2 == 1 || nb_squote % 2 == 1)
		return (true);
	return (false);
}
char	*remove_quote(char *str, int quote_idx)
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


void	empty_quote(t_token *current)
{
	char *str;
	int		i;
	
	str = current->content;
	i = 0;
	while (str[i])
	{
		if ((str[i] == '"' && str[i + 1] == '"') || (str[i] == '\'' && str[i + 1] == '\''))
		{
			current->content = remove_quote(str, i);
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
		empty_quote(current);
		current = current->next;
		size_list--;
	}
}