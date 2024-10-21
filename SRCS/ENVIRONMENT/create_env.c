/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: art3mis <art3mis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 04:28:04 by pmateo            #+#    #+#             */
/*   Updated: 2024/10/21 22:00:07 by art3mis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	create_env_list(t_env_lst **env, char **envp)
{
	int			i;
	t_env_lst	*var;
	t_env_lst	*last;

	i = 0;
	if (envp == NULL)
		return (FAILURE);
	var = NULL;
	last = NULL;
	while (envp[i] != NULL)
	{
		var = env_new_var(envp[i]);
		secure_malloc(var, true);
		if (last == NULL)
			*env = var;
		else
			last->next = var;
		last = var;
		i++;
	}
	return (SUCCESS);
}

int	create_exp_env_list(t_env_lst **exp_env, char **envp, size_t envp_size,
	size_t idx_exp_env)
{
	t_env_lst	*var_to_add;
	t_env_lst	*last;

	var_to_add = NULL;
	last = NULL;
	while (idx_exp_env != envp_size)
	{
		if (idx_exp_env == 0)
			var_to_add = copy_toppest(envp);
		else
			var_to_add = ascii_sort(envp, last->content);
		if (var_to_add == NULL)
		{
			lstclear_env(exp_env);
			return (FAILURE);
		}
		if (last == NULL)
			*exp_env = var_to_add;
		else
			last->next = var_to_add;
		last = var_to_add;
		idx_exp_env++;
	}
	return (SUCCESS);
}

static void	__update_shlvl(t_env_lst *env)
{
	t_env_lst	*current;
	int			var_value;
	char		*new_value;

	current = env;
	while (current != NULL)
	{
		if (ft_strncmp(current->content, "SHLVL=", 6) == 0)
		{
			var_value = ft_atoi(current->content + 6, 0);
			var_value += 1;
			new_value = ft_itoa(var_value);
			secure_malloc(new_value, true);
			(void)yama(ADD, new_value, 0);
			free(current->content);
			current->content = ft_strjoin("SHLVL=", new_value);
			secure_malloc(current->content, true);
			// (void)yama(ADD, current->content, 0);
			(void)yama(REMOVE, new_value, 0);
		}
		current = current->next;
	}
}

void	create_env(t_data *d, char **envp)
{
	size_t	envp_size;

	envp_size = get_envtab_size(envp);
	if (create_env_list(&(d->env), envp) == FAILURE)
		err_msg("An error occured with env_list", NULL, 0);
	__update_shlvl(d->env);
	if (create_exp_env_list(&(d->exp_env), envp, envp_size, 0) == FAILURE)
		err_msg("An error occured with export_env_list", NULL, 0);
}
