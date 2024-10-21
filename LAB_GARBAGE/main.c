/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmateo <pmateo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 14:41:52 by pmateo            #+#    #+#             */
/*   Updated: 2024/10/21 20:02:00 by pmateo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gc.h"

// int	main(void)
// {
// 	char 	**split;

// 	split = ft_split("Watashi wa Ana desu, ogenkisamade genki desu", ' ');
// 	(void)yama(ADD_TAB, split, 0);

// 	printf("-----------------test1---------------\n");
// 	// printf("split[0] =  %s ; ptr = %p\n", split[0], split);

// 	printf("-----------------clean all---------------\n");
// 	yama(CLEAN_ALL, 0, 0);
// 	// printf("split[0] =  %s ; ptr = %p\n", split[0], split);
// }

int	main(void)
{
	char 	*alloc1;
	char 	*alloc2;
	int		*alloc3;
	char	**tab;
	char	**tab_2;
	int		i;
	// char 	*alloc4;
	
	printf("-----------------test1---------------\n");
	tab = (char **)yama(CREATE_TAB, NULL, sizeof(char *) * 4);
	if (!tab)
		return (1);
	// secure_malloc(tab);
	tab[0] = (char *)yama(ADD, ft_strdup("Hello"), 0);
	tab[1] = (char *)yama(ADD, ft_strdup("World"), 0);
	tab[2] = (char *)yama(ADD, ft_strdup("Yama"), 0);
	tab[3] = NULL;
	printf("tab:\n");
	i = 0;
	while (tab[i] != NULL)
	{
		printf("  %s\n", tab[i]);
		i++;
	}
	yama(REMOVE, tab, 0);
	yama(PRINT_LST, NULL, 0);
	// tab = NULL;
	// printf("Removed tab\n");

	// printf("-----------------test2---------------\n");
	// tab_2 = (char **)yama(CREATE_TAB, NULL, sizeof(char *) * 3);
	// secure_malloc(tab_2);
	// tab_2[0] = (char *)yama(ADD, ft_strdup("New"), 0);
	// tab_2[1] = (char *)yama(ADD, ft_strdup("Table"), 0);
	// tab_2[2] = NULL;
	// printf("tab_2:\n");
	// i = 0;
	// while (tab_2[i] != NULL)
	// {
	// 	printf("  %s\n", tab_2[i]);
	// 	i++;
	// }
	
	// printf("-----------------test3---------------\n");
	// alloc1 = (char *)yama(CREATE, NULL, (5 * sizeof(char) + 1));
	// ft_strlcpy(alloc1, "hello", 6);
	// alloc2 = yama(ADD, ft_strdup("world"), 0);
	// alloc3 = malloc(sizeof(int));
	// *alloc3 = 42;
	// (void)yama(ADD, alloc3, 0);
	// // alloc4 = (char *)yama(CREATE, NULL, sizeof(char));
	// // *alloc4 = '*';
	// printf("alloc1 =  %s ; ptr = %p\n", alloc1, alloc1);
	// printf("alloc2 =  %s ; ptr = %p\n", alloc2, alloc2);
	// printf("alloc3 =  %d ; ptr = %p\n", *alloc3, alloc3);
	// // printf("alloc4 =  %c ; ptr = %p\n", *alloc4, alloc4);
	// // (void)yama(CLEAN_ALL, NULL, 0);
	
	// // printf("-----------------remove---------------\n");
	// // alloc1 = yama(REMOVE, alloc1, 0);
	// // alloc1 = NULL;
	// // alloc2 = yama(REMOVE, alloc2, 0);
	// // alloc3 = yama(REMOVE, alloc3, 0);
	// // alloc3 = NULL;
	// // printf("alloc1 =  %s ; ptr = %p\n", alloc1, alloc1);
	// // printf("alloc2 =  %s ; ptr = %p\n", alloc2, alloc2);
	// // printf("alloc3 ptr = %p\n", alloc3);
	// // printf("-----------------test2---------------\n");
	// // alloc1 = (char *)yama(CREATE, NULL, (5 * sizeof(char) + 1));
	// // ft_strlcpy(alloc1, "hello", 6);
	// // alloc2 = yama(ADD, ft_strdup("world"), 0);
	// // alloc3 = (int *)yama(CREATE, NULL, (sizeof(int)));
	// // printf("alloc1 =  %s ; ptr = %p\n", alloc1, alloc1);
	// // printf("alloc2 =  %s ; ptr = %p\n", alloc2, alloc2);
	// // printf("alloc3 =  %d ; ptr = %p\n", *alloc3, alloc3);
	
	// printf("-----------------clean all---------------\n");
	// yama(CLEAN_ALL, 0, 0);
	// // printf("alloc1 =  %s ; ptr = %p\n", alloc1, alloc1);
	// // printf("alloc2 =  %s ; ptr = %p\n", alloc2, alloc2);
	// // printf("ptr = %p\n", alloc3);
	// // printf("alloc4 =  %c ; ptr = %p\n", *alloc4, alloc4);
	// printf("All memory cleaned with yama(CLEAN_ALL)\n");
}