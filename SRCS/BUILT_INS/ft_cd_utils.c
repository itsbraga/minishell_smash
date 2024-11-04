/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: art3mis <art3mis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 10:42:55 by art3mis           #+#    #+#             */
/*   Updated: 2024/11/04 01:43:54 by art3mis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

static char	*__update_pwd(t_env_lst **env, char **old_pwd)
{
	t_env_lst	*curr;
	char		*new_pwd;

	new_pwd = getcwd(NULL, 0);
	if (new_pwd == NULL)
	{
		err_msg("0: getcwd() failed", ERR_BAD_FILE, 0);
		return (NULL);
	}
	curr = *env;
	while (curr != NULL)
	{
		if (ft_strncmp(curr->content, "PWD=", 4) == 0)
		{
			*old_pwd = ft_strdup(curr->content);
			free(curr->content);
			curr->content = ft_strjoin("PWD=", new_pwd);
			if (curr->content == NULL)
				(free(new_pwd), clean_exit(FAILURE));
		}
		curr = curr->next;
	}
	return (new_pwd);
}

static void	__update_oldpwd(t_env_lst **env, char *old_pwd)
{
	t_env_lst	*curr;

	curr = *env;
	while (curr != NULL)
	{
		if ((ft_strncmp(curr->content, "OLDPWD=", 7) == 0) && old_pwd != NULL)
		{
			free(curr->content);
			curr->content = ft_strjoin("OLDPWD=", old_pwd + 4);
			secure_malloc(curr->content, true);
			free_and_set_null((void **)&old_pwd);
			break ;
		}
		curr = curr->next;
	}
}

void	change_paths(t_env_lst **env, t_env_lst **exp_env)
{
	char	*old_pwd;
	char	*new_pwd;
	char	*exp_old_pwd;
	char	*exp_new_pwd;

	new_pwd = __update_pwd(env, &old_pwd);
	if (new_pwd == NULL)
		return ;
	exp_old_pwd = NULL;
	exp_new_pwd = __update_pwd(exp_env, &exp_old_pwd);
	if (exp_new_pwd == NULL)
		return ;
	__update_oldpwd(env, old_pwd);
	__update_oldpwd(exp_env, exp_old_pwd);
	free_and_set_null((void **)&new_pwd);
	free_and_set_null((void **)&exp_new_pwd);
}

int	is_directory(const char *path)
{
	struct stat	path_stat;

	if (lstat(path, &path_stat) == -1)
	{
		if (errno == EACCES)
			return (1);
		return (-1);
	}
	return (S_ISDIR(path_stat.st_mode));
}
