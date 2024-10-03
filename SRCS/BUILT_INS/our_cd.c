/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   our_cd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: art3mis <art3mis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 15:41:26 by annabrag          #+#    #+#             */
/*   Updated: 2024/10/03 23:20:39 by art3mis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*__find_var_path(char *to_find, t_env_lst *env)
{
	t_env_lst	*head;
	char		*path;
	size_t		len_var_env;
	size_t		len_to_find;

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
			if (path == NULL)
			{
				free(path);
				return (NULL);
			}
			return (path);
		}
		head = head->next;
	}
	return (NULL);
}

static int	__go_to_env_var(t_env_lst *env, char *var, t_token_dblst *t)
{
	char	*var_path;
	int		ret;
	char	*current;
	char	*next;
	int		error;

	var_path = __find_var_path(var, env);
	ret = chdir((const char *)var_path);
	if (ret != 0)
	{
		current = t->content;
		next = t->next->content;
		error = err_msg_cmd(current, next, "No such file or directory", 1);
		free(current);
		free(next);
		return (error);
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
int	our_cd(t_data *d)
{
	int		ret;
	char	*current;
	char	*next;
	int		error;
	
	if ((d->token->next == NULL)
		|| (ft_strcmp((const char *)d->token->next->content, "~") == 0))
		ret = __go_to_env_var(d->env, "HOME=", d->token);
	else if (ft_strcmp((const char *)d->token->next->content, "-") == 0)
	{
		ret = __go_to_env_var(d->env, "OLDPWD=", d->token);
		printf("%s\n", __find_var_path("OLDPWD=", d->env));
	}
	else
		ret = chdir((const char *)d->token->next->content);
	if (ret != 0)
	{
		current = d->token->content;
		next = d->token->next->content;
		error = err_msg_cmd(current, next, "No such file or directory", 1);
		return (free(current), free(next), error);
	}
	change_paths(d->env, d->exp_env);
	// d->last_exit_status = 0;
	return (SUCCESS);
}
