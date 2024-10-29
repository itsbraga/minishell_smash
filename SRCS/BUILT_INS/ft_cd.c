/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: annabrag <annabrag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 15:41:26 by annabrag          #+#    #+#             */
/*   Updated: 2024/10/29 17:02:58 by annabrag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

static char	*__find_var_path(char *to_find, t_env_lst *env)
{
	t_env_lst	*curr;
	char		*path;
	size_t		len_var_env;
	size_t		len_to_find;

	curr = env;
	path = NULL;
	len_to_find = ft_strlen(to_find);
	while (curr != NULL)
	{
		len_var_env = ft_strlen(curr->content);
		if (ft_strncmp(curr->content, to_find, len_to_find) == 0)
		{
			path = ft_substr(curr->content, len_to_find,
					(len_var_env - len_to_find));
			secure_malloc(path, true);
			return (path);
		}
		curr = curr->next;
	}
	return (NULL);
}

static int	__go_to_env_var(t_env_lst *env, char *var, t_token_dblst *t)
{
	char	*var_path;
	int		ret;
	char	*next;
	int		error;

	var_path = __find_var_path(var, env);
	ret = chdir(var_path);
	if (ret != 0)
	{
		next = t->next->content;
		error = err_msg_cmd(t->content, next, ERR_BAD_FILE, FAILURE);
		free_and_set_null(next);
		return (error);
	}
	if (var_path != NULL)
		free_and_set_null(var_path);
	return (ret);
}

static int	__handle_cd_error(char *path)
{
	const int	is_dir = is_directory(path);
	int			error;

	error = 0;
	if (is_dir == 0)
		error = err_msg_cmd("cd", path, ERR_NOT_DIR, FAILURE);
	else if (is_dir == -1)
		error = err_msg_cmd("cd", path, ERR_BAD_FILE, FAILURE);
	return (ft_exit_status(error, ADD));
}

int	ft_cd(t_data *d)
{
	int			ret;
	char		*path;
	t_prompt	pr;

	path = d->token->next->content;
	if ((d->token->next == NULL)
		|| (ft_strcmp(path, "~") == 0))
		ret = __go_to_env_var(d->env, "HOME=", d->token);
	else if (ft_strcmp(path, "-") == 0)
	{
		ret = __go_to_env_var(d->env, "OLDPWD=", d->token);
		ft_printf(STDOUT_FILENO, "%s\n", __find_var_path("OLDPWD=", d->env));
	}
	else
		ret = chdir(path);
	if (ret != 0)
		return (__handle_cd_error(path));
	change_paths(d->env, d->exp_env);
	update_prompt(d, &pr);
	return (ft_exit_status(ret, ADD));
}
