/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: art3mis <art3mis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 18:29:36 by pmateo            #+#    #+#             */
/*   Updated: 2024/10/21 22:07:22 by art3mis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "INCLUDES/libft.h"

char	*ft_strdup(const char *s1)
{
	size_t	size;
	char	*s2;

	if (s1 == NULL)
		return (NULL);
	size = ft_strlen(s1) + 1;
	s2 = malloc(size * sizeof(char));
	if (s2 == NULL)
		return (NULL);
	ft_strlcpy(s2, s1, size);
	return (s2);
}

// int	main(void)
// {
// 	char *str = "copiemoi";
// 	printf("ma version renvoie %s\n", ft_strdup(str));
// 	printf("la vraie version renvoie %s", strdup(str));
// 	return (0);
// }
// int	main(void)
// {
// 	char *s = ft_strdup((char*)"coucou");
// 	printf("%s\n", s);
// 	s = strdup((char *)"coucou");
// 	printf("%s\n", s);
// }