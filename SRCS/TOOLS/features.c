/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   features.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: art3mis <art3mis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 00:29:12 by art3mis           #+#    #+#             */
/*   Updated: 2024/08/27 00:51:13 by art3mis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	rainbow_txt(const char *str)
{
	const char	*colors[7] = {RED, YELLOW, GREEN, CYAN, BLUE, PURPLE, PINK};
	size_t		nb_colors;
	size_t		i;
	size_t		len;

	nb_colors = sizeof(colors) / sizeof(colors[0]);
	i = 0;
	len = ft_strlen(str);
	while (i < len)
	{
		printf("%s%c", colors[i % nb_colors], str[i]);
		i++;
	}
	printf("%s\n", RESET);
}

void	rainbow_txt_nonl(const char *str)
{
	const char	*colors[7] = {RED, YELLOW, GREEN, CYAN, BLUE, PURPLE, PINK};
	size_t		nb_colors;
	size_t		i;
	size_t		len;

	nb_colors = sizeof(colors) / sizeof(colors[0]);
	i = 0;
	len = ft_strlen(str);
	while (i < len)
	{
		printf("%s%c", colors[i % nb_colors], str[i]);
		i++;
	}
	printf(RESET);
}

char	*rainbow_prompt(const char *str)
{
    const char	*colors[7] = {RED, YELLOW, GREEN, CYAN, BLUE, PURPLE, PINK};
    char		*colored_str;
    char		*tmp;
    size_t		i;
	size_t		len;

	tmp = NULL;
	i = 0;
	len = ft_strlen(str);
	colored_str = malloc(len * 10);
    if (colored_str == NULL)
        return (NULL);
    colored_str[0] = '\0';
    while (str[i] != '\0')
    {
        tmp = ft_strjoin(colored_str, colors[i % 7]);
        free(colored_str);
        colored_str = ft_strjoin(tmp, (char[]){str[i], '\0'});
        free(tmp);
        i++;
    }
    tmp = ft_strjoin(colored_str, RESET);
    free(colored_str);
    return (tmp);
}
