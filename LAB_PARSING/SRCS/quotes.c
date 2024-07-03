/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmateo <pmateo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 20:42:22 by pmateo            #+#    #+#             */
/*   Updated: 2024/07/04 00:19:19 by pmateo           ###   ########.fr       */
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

char	*empty_quote(char *str)
{
	char	*res;
	char	*start;
	char 	*to_join;
	char 	*tmp;
	
	res = ft_strdup(str);
	while (*res)
	{
		start = res;
		tmp = res;
		if (*res == '"' && *res + 1 == '"')
		{
			to_join = *res + 2;
			*res = '\0';
			res = ft_strjoin("")
		}
	}
}

void	handle_quotes(t_token **t)
{
	size_t	size_list;
	t_token *current;
	
	size_list = get_tlist_size(t);
	current = *t;
	while (size_list)
	{
		if (unclosed_quotes(current->content) == true)
			quote_exit();
		empty_quote(current->content);
		current = current->next;
		size_list--;
	}
}