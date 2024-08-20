/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: annabrag <annabrag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 20:26:55 by annabrag          #+#    #+#             */
/*   Updated: 2024/08/20 20:29:11 by annabrag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "built_ins.h"

t_env	*e_new_node(char *content)
{
	t_env	*new_node;
	
	new_node = malloc(sizeof(t_env));
	if (!new_node)
		return (NULL);
	new_node->content = content;
	new_node->next = NULL;
	return (new_node);
}

t_env	*e_last_node(t_env *e)
{
	if (!e)
		return (NULL);
	while (e->next != NULL)
		e = e->next;
	return (e);
}

void	e_add_back(t_env **e, t_env *new_node)
{
	t_env	*tmp;

	if (!(*e))
		*e = new_node;
	else
	{
		tmp = e_last_node(*e);
		tmp->next = e_new_node;
	}
}
