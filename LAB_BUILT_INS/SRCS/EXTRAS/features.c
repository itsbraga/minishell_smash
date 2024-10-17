/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   features.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: annabrag <annabrag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 00:29:12 by art3mis           #+#    #+#             */
/*   Updated: 2024/10/17 16:39:40 by annabrag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "my_builtins.h"

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
	int			i;

	colored_str = malloc(ft_strlen(str) * (10 + 4) + ft_strlen(RESET) + 5);
	if (colored_str == NULL)
		return (NULL);
	colored_str[0] = '\0';
	i = 0;
	ft_strcat(colored_str, "\001" BOLD "\002");
	while (str[i] != '\0')
	{
		ft_strcat(colored_str, "\001");
		ft_strcat(colored_str, (char *)colors[i % 7]);
		ft_strcat(colored_str, "\002");
		ft_strcat(colored_str, (char []){str[i], '\0'});
		i++;
	}
	ft_strcat(colored_str, "\001" RESET "\002");
	return (colored_str);
}
