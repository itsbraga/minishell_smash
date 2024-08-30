/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: annabrag <annabrag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 15:41:26 by annabrag          #+#    #+#             */
/*   Updated: 2024/08/30 20:55:36 by annabrag         ###   ########.fr       */
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

static int	__go_to_env_var(t_global *g, char *var)
{
	char	*var_path;
	int		ret;

	var_path = __find_var_path(var, g->env);
	ret = chdir((const char *)var_path);
	if (ret != 0)
	{
		errmsg_exit_status(g->token->content, &g->token->next->content, errno);
		// exit(errno);
	}
	if (var_path != NULL)
		free(var_path);
	return (ret);
}

/*	The tilde character (“~”) has a special meaning.
	When used at the beginning of a word, it expands
	into the name of the home directory of the named
	user, or if no user is named, the home directory
	of the current user
	
	>> bonus wildcards
*/
int	my_cd(t_global *g)
{
	int	ret;
	
	if ((g->token->next == NULL)
		|| (ft_strcmp((const char *)g->token->next->content, "~") == 0))
		ret = __go_to_env_var(g, "HOME=");
	else if (ft_strcmp((const char *)g->token->next->content, "-") == 0)
	{
		ret = __go_to_env_var(g, "OLDPWD=");
		printf("%s\n", __find_var_path("OLDPWD=", g->env));
	}
	else
		ret = chdir((const char *)g->token->next->content);
	if (ret != 0)
		errmsg_exit_status(g->token->content, &g->token->next->content, errno);
	change_paths(g->env, g->exp_env);
	g->last_exit_status = 0;
	return (SUCCESS);
}
