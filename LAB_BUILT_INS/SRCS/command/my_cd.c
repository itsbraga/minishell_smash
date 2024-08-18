/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: art3mis <art3mis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 15:41:26 by annabrag          #+#    #+#             */
/*   Updated: 2024/08/18 23:15:47 by art3mis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "built_ins.h"

/*	Recherche une variable d'environnement spécifique dans env (g->env),
	puis retourne la valeur associée si elle est trouvée
*/
static char	*__find_var_path(char *to_find, t_global *g)
{
	char	*path;
	int		i;
	int		len_var;

	path = NULL;
	i = 0;
	len_var = ft_strlen(to_find);
	while (g->env[i] != NULL)
	{
		if (ft_strncmp(g->env[i], to_find, len_var) == 0)
		{
			path = ft_substr(g->env[i], len_var, (ft_strlen(g->env[i]) - len_var));
			return (path);
		}
		i++;
	}
	return (NULL);
}

int	go_to_env_var(t_global *g, char *var)
{
	char	*var_path;
	int		cd_ret;

	var_path = __find_var_path(var, g);
	cd_ret = chdir(var_path);
	free(var_path);
	if (cd_ret != 0)
	{
		printf("%s%s%s%s\n", BOLD RED, "minishell: cd: ", RESET, strerror(errno));
		return (EXIT_FAILURE);
	}
	return (cd_ret);
}

void	update_path_in_env(t_global *g)
{
	char	cwd[PATH_MAX];
	char	*tmp;
	char	*old_pwd;
	int		i;

	if ((*cwd = getcwd(NULL, sizeof(cwd))) == NULL)
	{
		printf("%s%s%s\n", BOLD RED "minishell: ", RESET "getcwd: ", strerror(errno));
		return (EXIT_FAILURE);
	}
	old_pwd = getenv("PWD");
	i = 0;
	while (g->env[i] != NULL)
	{
		if (ft_strncmp(g->env[i], "PWD=", 4) == 0)
		{
			tmp = ft_strjoin("PWD=", cwd);
			free(g->env[i]);
			g->env[i] = tmp;
		}
		else if (ft_strncmp(g->env[i], "OLDPWD=", 7) == 0)
		{
			if (old_pwd != NULL)
				tmp = ft_strjoin("OLDPWD=", old_pwd);
			else
				tmp = ft_strjoin("OLDPWD=", "");
			free(g->env[i]);
			g->env[i] = tmp;
		}
		i++;
	}
}

int	my_cd(t_global *g);
