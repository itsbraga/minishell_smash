/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: art3mis <art3mis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 15:41:26 by annabrag          #+#    #+#             */
/*   Updated: 2024/10/17 11:02:32 by art3mis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "my_builtins.h"

static char	*__find_var_path(char *to_find, t_env_lst *env)
{
	t_env_lst	*head;
	char		*path;
	int			len_var_env;
	int			len_to_find;

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
				err_msg("malloc", ERR_MALLOC_LST, 0);
				exit(FAILURE);
			}
			return (path);
		}
		head = head->next;
	}
	free(path);
	return (NULL);
}

static int	__go_to_env_var(t_env_lst *env, char *var, t_token *t)
{
	char	*var_path;
	int		ret;

	var_path = __find_var_path(var, env);
	ret = chdir((const char *)var_path);
	if (ret != 0)
		return (err_msg_cmd(t->content, t->next->content, "No such file or directory", 1));
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
	int			ret;
	t_prompt	pr;
	
	if ((g->token->next == NULL)
		|| (ft_strcmp(g->token->next->content, "~") == 0))
		ret = __go_to_env_var(g->env, "HOME=", g->token);
	else if (ft_strcmp(g->token->next->content, "-") == 0)
	{
		ret = __go_to_env_var(g->env, "OLDPWD=", g->token);
		printf("%s\n", __find_var_path("OLDPWD=", g->env));
	}
	else
		ret = chdir(g->token->next->content);
	if (ret != 0)
		return (err_msg_cmd(g->token->content, g->token->next->content, "No such file or directory", 1));
	change_paths(g->env, g->exp_env);
	if (g->prompt != NULL)
		free(g->prompt);
	g->prompt = generate_prompt(&pr);
	// g->last_exit_status = 0;
	return (SUCCESS);
}
