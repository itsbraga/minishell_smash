/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: annabrag <annabrag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 14:41:52 by pmateo            #+#    #+#             */
/*   Updated: 2024/09/19 18:04:03 by annabrag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gc.h"

size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

size_t	ft_strlcpy(char *dest, const char *src, size_t size)
{
	unsigned int	i;

	i = 0;
	if (size == 0)
		return (ft_strlen(src));
	while (src[i] != '\0' && i < size - 1)
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (ft_strlen(src));
}

char	*ft_strdup(const char *s1)
{
	size_t	size;
	char	*s2;

	size = ft_strlen(s1) + 1;
	s2 = malloc(size * sizeof(char));
	if (s2 == NULL)
		return (NULL);
	ft_strlcpy(s2, s1, size);
	return (s2);
}

int	main(void)
{
	char 	**split;

	split = ft_split("Watashi wa Ana desu, ogenkisamade genki desu", ' ');
	(void)yama(ADD_TAB, split, 0);

	printf("-----------------test1---------------\n");
	printf("split[0] =  %s ; ptr = %p\n", split[0], split);

	printf("-----------------clean all---------------\n");
	yama(CLEAN_ALL, 0, 0);
	printf("split[0] =  %s ; ptr = %p\n", split[0], split);
}

//alloc1 = hello
//alloc2 = world
//alloc3 = 42;
//alloc4 = *;

// int	main(void)
// {
// 	char 	*alloc1;
// 	char 	*alloc2;
// 	int		*alloc3;
// 	// char 	*alloc4;

// 	printf("-----------------test1---------------\n");
// 	alloc1 = (char *)yama(CREATE, NULL, (5 * sizeof(char) + 1));
// 	ft_strlcpy(alloc1, "hello", 6);
// 	alloc2 = yama(ADD, ft_strdup("world"), 0);
// 	alloc3 = malloc(sizeof(int *));
// 	*alloc3 = 42;
// 	(void)yama(ADD, alloc3, 0);
// 	// alloc4 = (char *)yama(CREATE, NULL, sizeof(char));
// 	// *alloc4 = '*';
// 	printf("alloc1 =  %s ; ptr = %p\n", alloc1, alloc1);
// 	printf("alloc2 =  %s ; ptr = %p\n", alloc2, alloc2);
// 	printf("alloc3 =  %d ; ptr = %p\n", *alloc3, alloc3);
// 	// printf("alloc4 =  %c ; ptr = %p\n", *alloc4, alloc4);
// 	// (void)yama(CLEAN_ALL, NULL, 0);
// 	// printf("-----------------remove---------------\n");
// 	// alloc1 = yama(REMOVE, alloc1, 0);
// 	// alloc2 = yama(REMOVE, alloc2, 0);
// 	// alloc3 = yama(REMOVE, alloc3, 0);
// 	// printf("alloc1 =  %s ; ptr = %p\n", alloc1, alloc1);
// 	// printf("alloc2 =  %s ; ptr = %p\n", alloc2, alloc2);
// 	// printf("alloc3 ptr = %p\n", alloc3);
// 	// printf("-----------------test2---------------\n");
// 	// alloc1 = (char *)yama(CREATE, NULL, (5 * sizeof(char) + 1));
// 	// ft_strlcpy(alloc1, "hello", 6);
// 	// alloc2 = yama(ADD, ft_strdup("world"), 0);
// 	// alloc3 = (int *)yama(CREATE, NULL, (sizeof(int)));
// 	// printf("alloc1 =  %s ; ptr = %p\n", alloc1, alloc1);
// 	// printf("alloc2 =  %s ; ptr = %p\n", alloc2, alloc2);
// 	// printf("alloc3 =  %d ; ptr = %p\n", *alloc3, alloc3);
// 	printf("-----------------clean all---------------\n");
// 	yama(CLEAN_ALL, 0, 0);
// 	printf("alloc1 =  %s ; ptr = %p\n", alloc1, alloc1);
// 	printf("alloc2 =  %s ; ptr = %p\n", alloc2, alloc2);
// 	printf("ptr = %p\n", alloc3);
// 	// printf("alloc4 =  %c ; ptr = %p\n", *alloc4, alloc4);
// }