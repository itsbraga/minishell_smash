/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: annabrag <annabrag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 10:42:55 by art3mis           #+#    #+#             */
/*   Updated: 2024/10/23 21:07:47 by annabrag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

static char	*__update_pwd(t_env_lst *env, char **old_pwd)
{
	t_env_lst	*curr;
	char		*new_pwd;

	new_pwd = getcwd(NULL, 0);
	if (new_pwd == NULL)
	{
		err_msg("getcwd()", ERR_BAD_FILE, 0);
		// err_msg("0: getcwd() failed", ERR_BAD_FILE, 0);
		return (NULL);
	}
	curr = env;
	while (curr != NULL)
	{
		if (ft_strncmp(curr->content, "PWD=", 4) == 0)
		{
			*old_pwd = ft_strdup(curr->content);
			free(curr->content);
			curr->content = ft_strjoin("PWD=", new_pwd);
			if (curr->content == NULL)
				(free(new_pwd), exit(FAILURE));
		}
		curr = curr->next;
	}
	return (new_pwd);
}

static void	__update_oldpwd(t_env_lst *env, char *old_pwd)
{
	t_env_lst	*curr;

	curr = env;
	while (curr != NULL)
	{
		if ((ft_strncmp(curr->content, "OLDPWD=", 7) == 0)
			&& old_pwd != NULL)
		{
			free(curr->content);
			curr->content = ft_strjoin("OLDPWD=", old_pwd + 4);
			secure_malloc(curr->content, true);
			free_and_set_null(old_pwd);
			break ;
		}
		curr = curr->next;
	}
	// if (old_pwd != NULL)
	// 	free(old_pwd);
}

void	change_paths(t_env_lst *env, t_env_lst *exp_env)
{
	char	*old_pwd;
	char	*new_pwd;
	char	*exp_old_pwd;
	char	*exp_new_pwd;

	// old_pwd = NULL;
	new_pwd = __update_pwd(env, &old_pwd);
	if (new_pwd == NULL)
		return ;
	exp_old_pwd = NULL;
	exp_new_pwd = __update_pwd(exp_env, &exp_old_pwd);
	if (exp_new_pwd == NULL)
		return ;
	__update_oldpwd(env, old_pwd);
	__update_oldpwd(exp_env, exp_old_pwd);
	free_and_set_null(new_pwd);
	free_and_set_null(exp_new_pwd);
}