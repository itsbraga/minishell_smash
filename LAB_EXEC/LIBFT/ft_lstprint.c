/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstprint.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmateo <pmateo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 02:52:47 by pmateo            #+#    #+#             */
/*   Updated: 2024/06/05 19:43:29 by pmateo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "INCLUDES/libft.h"

void	ft_lstprint(t_list *lst)
{
	while (lst)
	{
		ft_printf(1, "&cell = %p\n", lst);
		ft_printf(1, "content_cell = %d\n", *((int *)lst->content));
		ft_printf(1, "&next_cell = %p\n", lst->next);
		ft_printf(1, "|\n|\n|\n");
		lst = lst->next;
	}
	ft_printf(1, "&cell = NULL\n");
	ft_printf(1, "content_cell = NULL\n");
	ft_printf(1, "&next_cell = NULL\n");
}
