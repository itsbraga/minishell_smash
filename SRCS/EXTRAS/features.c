/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   features.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: annabrag <annabrag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 00:29:12 by art3mis           #+#    #+#             */
/*   Updated: 2024/10/08 18:46:50 by annabrag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	rainbow_txt(const char *str)
{
	const char	*colors[7] = {RED, YELLOW, GREEN, CYAN, BLUE, PURPLE, PINK};
	int			nb_colors;
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
	printf("%s\n", R);
}

void	rainbow_txt_nonl(const char *str)
{
	const char	*colors[7] = {RED, YELLOW, GREEN, CYAN, BLUE, PURPLE, PINK};
	int			nb_colors;
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
	printf(R);
}

char	*rainbow_prompt(const char *str)
{
	const char	*colors[7] = {RED, YELLOW, GREEN, CYAN, BLUE, PURPLE, PINK};
	char		*colored_str;
	int			i;
	size_t		len;

	len = ft_strlen(str) * (10 + 4) + ft_strlen(R) + 5;
	colored_str = yama(CREATE, NULL, len);
	secure_malloc(colored_str);
	colored_str[0] = '\0';
	i = 0;
	ft_strcat(colored_str, "\001" BOLD "\002");
	while (str[i] != '\0')
	{
		ft_strcat(colored_str, "\001");
		ft_strcat(colored_str, (char *)colors[i % 7]);
		ft_strcat(colored_str, "\002");
		ft_strcat(colored_str, (char[]){str[i], '\0'});
		i++;
	}
	ft_strcat(colored_str, "\001" R "\002");
	return (colored_str);
}
