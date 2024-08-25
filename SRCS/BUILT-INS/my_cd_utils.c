/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_cd_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: annabrag <annabrag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 10:42:55 by art3mis           #+#    #+#             */
/*   Updated: 2024/08/25 15:28:48 by annabrag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*__find_var_path(char *to_find, t_env *env)
{
	t_env	*head;
	char	*path;
	int		len_var_env;
	int		len_to_find;

	head = env;
	path = NULL;
	len_to_find = ft_strlen(to_find);
	while (head != NULL)
	{
		len_var_env = ft_strlen(head->content);
		if (ft_strncmp(head->content, to_find, len_to_find) == 0)
		{
			path = ft_substr(head->content, len_to_find,
					(len_var_env - len_to_find));
			return (path);
		}
		head = head->next;
	}
	return (NULL);
}

int go_to_env_var(t_global *g, char *var)
{
	char	*var_path;
	int		ret;

	var_path = __find_var_path(var, g->env);
	ret = chdir((const char *)var_path);
	if (ret != 0)
	{
		printf("%s %s: ", BOLD RED "minishell:" RESET, g->token->content);
		printf("%s: %s\n", g->token->next->content, strerror(errno));
		return (EXIT_FAILURE);
	}
	if (var_path != NULL)
		free(var_path);
	return (ret);
}
