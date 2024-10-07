/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: art3mis <art3mis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 10:54:57 by u4s2e0r           #+#    #+#             */
/*   Updated: 2024/10/07 19:05:12 by art3mis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "INCLUDES/libft.h"

char	*ft_substr(const char *src, unsigned int start, size_t len)
{
	char	*str;
	size_t	strlen;

	if (!src)
		return (NULL);
	if (start > ft_strlen(src))
	{
		str = malloc(sizeof(char));
		if (!str)
			return (NULL);
		str[0] = '\0';
		return (str);
	}
	else
	{
		strlen = len;
		if (ft_strlen(src + start) < len)
			strlen = ft_strlen(src + start);
		str = malloc((strlen + 1) * sizeof(char));
		if (!str)
			return (NULL);
		ft_strlcpy(str, src + start, strlen + 1);
		return (str);
	}
}

// int	main(void)
// {
// 	const char *src = "extraismoideca";
// 	int start = 7;
// 	int len = 3;
// 	printf("la fonction ft_substr renvoie %s\n", ft_substr(src, start, len));
// 	return (0);
// }
