/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_token_and_exec_lsts.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: art3mis <art3mis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 21:55:22 by art3mis           #+#    #+#             */
/*   Updated: 2024/10/12 01:41:58 by art3mis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	create_token_and_exec_lsts(t_data *d)
{
	t_exec_lst	*new_task;
	
	while (d->main != NULL)
	{
		if (create_tokens(d) == FAILURE)
		{
			err_msg(NULL, "unable to create t_token_dblst\n", 0);
			return (FAILURE);
		}
		new_task = exec_lst_new_node();
		secure_malloc(new_task);
		new_task = create_exec_tasks2(d);
		exec_lst_add_back(&(d->exec), new_task);
		// if (create_exec_tasks2(d) == FAILURE)
		// {
		// 	err_msg(NULL, "unable to create t_exec_lst\n", 0);
		// 	return (FAILURE);
		// }
		d->main = d->main->next;
	}
	return (SUCCESS);
}
