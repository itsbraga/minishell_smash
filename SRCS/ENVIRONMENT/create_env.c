/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: annabrag <annabrag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 04:28:04 by pmateo            #+#    #+#             */
/*   Updated: 2024/10/31 13:01:23 by annabrag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

static void	__update_shlvl(t_env_lst *env)
{
	t_env_lst	*curr;
	int			var_value;
	char		*new_value;

	curr = env;
	while (curr != NULL)
	{
		if (ft_strncmp(curr->content, "SHLVL=", 6) == 0)
		{
			var_value = ft_atoi(curr->content + 6, 0);
			var_value += 1;
			new_value = ft_itoa(var_value);
			secure_malloc(new_value, true);
			(void)yama(ADD, new_value, 0);
			free(curr->content);
			curr->content = ft_strjoin("SHLVL=", new_value);
			secure_malloc(curr->content, true);
			(void)yama(REMOVE, new_value, 0);
		}
		curr = curr->next;
	}
}

void	create_env(t_data *d, char **envp)
{
	size_t	envp_size;

	envp_size = get_env_tab_size(envp);
	if (__create_env_list(d, envp) == FAILURE)
		err_msg("An error occured with env_list", NULL, 0);
	__update_shlvl(d->env);
	if (__create_exp_env_list(d, envp, envp_size, 0) == FAILURE)
		err_msg("An error occured with export_env_list", NULL, 0);
}
