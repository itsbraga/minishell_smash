/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rainbow_txt.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: annabrag <annabrag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 00:29:12 by art3mis           #+#    #+#             */
/*   Updated: 2024/11/04 19:15:12 by annabrag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tools.h"

static void	__init_rainbow_txt(const char *str, t_rainbow_txt *rb)
{
	rb->len = (ft_strlen(str) * 5000);
	rb->colored_str = yama(CREATE, NULL, rb->len);
	secure_malloc(rb->colored_str, true);
	rb->colored_str[0] = '\0';
	rb->i = 0;
}

static bool	__is_acronym(const char *str, t_rainbow_txt *rb)
{
	if (str[rb->i] == 'S' || str[rb->i] == 'M' || str[rb->i] == 'A'
		|| str[rb->i] == 'H')
		return (true);
	else
		return (false);
}

char	*rainbow_banner(const char *str)
{
	t_rainbow_txt	rb;
	const char		*colors[6] = {PGG, PO, PG, PB, PP, PINK};

	__init_rainbow_txt(str, &rb);
	ft_strcat(rb.colored_str, "\001" BOLD "\002");
	while (str[rb.i] != '\0')
	{
		if (__is_acronym(str, &rb) == true)
		{
			ft_strcat(rb.colored_str, "\001");
			ft_strcat(rb.colored_str, RED);
			ft_strcat(rb.colored_str, "\002");
			ft_strcat(rb.colored_str, (char []){str[rb.i], '\0'});
		}
		else
		{
			ft_strcat(rb.colored_str, "\001");
			ft_strcat(rb.colored_str, (char *)colors[rb.i % 6]);
			ft_strcat(rb.colored_str, "\002");
			ft_strcat(rb.colored_str, (char []){str[rb.i], '\0'});
		}
		rb.i++;
	}
	ft_strcat(rb.colored_str, "\001" R "\002");
	return (rb.colored_str);
}

char	*rainbow_prompt(const char *str)
{
	const char	*colors[7] = {RED, YELLOW, GREEN, CYAN, BLUE, PURPLE, PINK};
	char		*colored_str;
	int			i;
	size_t		len;

	len = (ft_strlen(str) * (10 + 4) + ft_strlen(R) + 5);
	colored_str = yama(CREATE, NULL, len);
	secure_malloc(colored_str, true);
	colored_str[0] = '\0';
	i = 0;
	while (str[i] != '\0')
	{
		ft_strcat(colored_str, "\001");
		ft_strcat(colored_str, (char *)colors[i % 7]);
		ft_strcat(colored_str, "\002");
		ft_strcat(colored_str, (char []){str[i], '\0'});
		i++;
	}
	return (colored_str);
}
