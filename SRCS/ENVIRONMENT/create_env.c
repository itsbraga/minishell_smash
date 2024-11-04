/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmateo <pmateo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 04:28:04 by pmateo            #+#    #+#             */
/*   Updated: 2024/11/04 19:01:30 by pmateo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static	char	**__handle_empty_envp(void)
{
	char	**new_envp;
	char	*actual_pwd;

	new_envp = malloc(4 * sizeof(char *));
	secure_malloc(new_envp, true);
	actual_pwd = getcwd(NULL, 0);
	new_envp[0] = ft_strjoin("PWD=", actual_pwd);
	new_envp[1] = ft_strjoin("OLDPWD=", actual_pwd);
	new_envp[2] = ft_strdup("SHLVL=1");
	new_envp[3] = NULL;
	free_and_set_null((void **)&actual_pwd);
	return (new_envp);
}

static int	__create_env_list(t_data *d, char **envp)
{
	int			i;
	t_env_lst	*new_var;

	i = 0;
	if (envp == NULL)
		return (FAILURE);
	new_var = NULL;
	while (envp[i] != NULL)
	{
		new_var = env_new_var(envp[i]);
		secure_malloc(new_var, true);
		env_lst_add_back(&(d->env), new_var);
		i++;
	}
	return (SUCCESS);
}

static int	__create_exp_env_list(t_data *d, char **envp, size_t envp_size,
size_t idx_exp_env)
{
	t_env_lst	*new_var;

	new_var = NULL;
	while (idx_exp_env != envp_size)
	{
		if (idx_exp_env == 0)
			new_var = copy_toppest(envp);
		else
			new_var = ascii_sort(envp, new_var->content);
		if (new_var == NULL)
		{
			lstclear_env(&(d->exp_env));
			return (FAILURE);
		}
		env_lst_add_back(&(d->exp_env), new_var);
		idx_exp_env++;
	}
	return (SUCCESS);
}

void	create_env(t_data *d, char **envp)
{
	bool	envp_has_been_rebuilt;
	size_t	envp_size;

	envp_has_been_rebuilt = false;
	envp_size = get_env_tab_size(envp);
	if (envp_size == 0)
	{
		envp = __handle_empty_envp();
		envp_size = get_env_tab_size(envp);
		envp_has_been_rebuilt = true;
	}
	if (__create_env_list(d, envp) == FAILURE)
		err_msg("An error occured with env_list", NULL, 0);
	if (envp_has_been_rebuilt == false)
		update_shlvl(&(d->env));
	dprintf(2, "envp_size = %ld\n", envp_size);
	if (__create_exp_env_list(d, envp, envp_size, 0) == FAILURE)
		err_msg("An error occured with export_env_list", NULL, 0);
	if (envp_has_been_rebuilt == false)
		update_shlvl_export(&(d->exp_env));
	if (envp_has_been_rebuilt == true)
		free_tab(envp);
}
