/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: art3mis <art3mis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 10:42:55 by art3mis           #+#    #+#             */
/*   Updated: 2024/10/21 00:08:04 by art3mis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*__update_pwd(t_env_lst *env, char **old_pwd)
{
	t_env_lst	*current;
	char		*new_pwd;

	new_pwd = getcwd(NULL, 0);
	if (new_pwd == NULL)
	{
		err_msg("0: getcwd() failed", ERR_BAD_FILE, 0);
		return (NULL);
	}
	current = env;
	while (current != NULL)
	{
		if (ft_strncmp(current->content, "PWD=", 4) == 0)
		{
			*old_pwd = ft_strdup(current->content);
			(void)yama(REMOVE, current->content, 0);
			current->content = ft_strjoin("PWD=", new_pwd);
			if (current->content == NULL)
				return (free(new_pwd), NULL);
			(void)yama(ADD, current->content, 0);
		}
		current = current->next;
	}
	return (new_pwd);
}

static void	__update_oldpwd(t_env_lst *env, char *old_pwd)
{
	t_env_lst	*current;

	current = env;
	while (current != NULL)
	{
		if ((ft_strncmp(current->content, "OLDPWD=", 7) == 0)
			&& old_pwd != NULL)
		{
			(void)yama(REMOVE, current->content, 0);
			current->content = ft_strjoin("OLDPWD=", old_pwd + 4);
			secure_malloc(current->content, true);
			(void)yama(ADD, current->content, 0);
			free(old_pwd);
			old_pwd = NULL;
			break ;
		}
		current = current->next;
	}
	if (old_pwd != NULL)
		free(old_pwd);
}

void	change_paths(t_env_lst *env, t_env_lst *exp_env)
{
	char	*old_pwd;
	char	*new_pwd;
	char	*exp_old_pwd;
	char	*exp_new_pwd;

	old_pwd = NULL;
	new_pwd = __update_pwd(env, &old_pwd);
	if (new_pwd == NULL)
		return ;
	exp_old_pwd = NULL;
	exp_new_pwd = __update_pwd(exp_env, &exp_old_pwd);
	if (exp_new_pwd == NULL)
		return ;
	__update_oldpwd(env, old_pwd);
	__update_oldpwd(exp_env, exp_old_pwd);
	free(new_pwd);
	free(exp_new_pwd);
}
