/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: annabrag <annabrag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 15:41:26 by annabrag          #+#    #+#             */
/*   Updated: 2024/11/04 19:24:50 by annabrag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

static bool	__bad_arguments(char **args)
{
	size_t	i;

	i = 0;
	while (args[i] != NULL)
		i++;
	if (i >= 3)
		return (true);
	else
		return (false);
}

static int	__handle_cd_error(char *path)
{
	const int	is_dir = is_directory(path);
	int			ret;

	ret = 0;
	if (is_dir == 0)
		ret = err_msg_cmd("cd", path, ERR_NOT_DIR, FAILURE);
	else if (is_dir == -1 || is_dir == 1)
		ret = err_msg_cmd("cd", path, strerror(errno), FAILURE);
	else
		ret = SUCCESS;
	return (ret);
}

static char	*__find_var_path(char *to_find, t_env_lst **env)
{
	t_env_lst	*curr;
	char		*path;
	size_t		len_var_env;
	size_t		len_to_find;

	curr = *env;
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

static int	__go_to_env_var(t_env_lst **env, char *var, char **args)
{
	int		ret;
	char	*var_path;

	ret = 0;
	var_path = __find_var_path(var, env);
	if (var_path == NULL)
	{
		if (args[1] == NULL)
			ret = err_msg_cmd("cd", NULL, "HOME not set", FAILURE);
		else if (ft_strcmp(args[1], "-") == 0)
			ret = err_msg_cmd("cd", NULL, "OLDPWD not set", FAILURE);
		return (ret);
	}
	ret = chdir(var_path);
	if (ret != 0)
		ret = __handle_cd_error(var_path);
	if (var_path != NULL)
		free_and_set_null((void **)&var_path);
	return (ret);
}

int	ft_cd(t_data *d, char **args)
{
	char		*path;
	int			ret;
	t_prompt	pr;

	if (__bad_arguments(args) == true)
		return (err_msg_cmd("cd", NULL, ERR_ARG, FAILURE));
	if (args[1] == NULL || ft_strcmp(args[1], "~") == 0)
		ret = __go_to_env_var(&(d->env), "HOME=", args);
	else if (ft_strcmp(args[1], "-") == 0)
	{
		ret = __go_to_env_var(&(d->env), "OLDPWD=", args);
		if (ret == 0)
		{
			path = __find_var_path("OLDPWD=", &(d->env));
			ft_printf(STDOUT_FILENO, "%s\n", path);
			free_and_set_null((void **)&path);
		}
	}
	else
		ret = chdir(args[1]);
	if (ret != 0)
		return (__handle_cd_error(args[1]));
	change_paths(&(d->env), &(d->exp_env));
	update_prompt(d, &pr);
	return (ft_exit_status(ret, ADD));
}
