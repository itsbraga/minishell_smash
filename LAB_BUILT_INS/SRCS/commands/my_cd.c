/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: annabrag <annabrag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 15:41:26 by annabrag          #+#    #+#             */
/*   Updated: 2024/08/19 20:14:16 by annabrag         ###   ########.fr       */
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

static int	__cd_to_env_var(t_global *g, char *var)
{
	char	*var_path;
	int		ret;

	var_path = __find_var_path(var, g);
	// printf("%s: %s\n", "CD_TO_ENV_VAR", var_path);
	ret = chdir((const char *)var_path);
	// printf("%s: %d\n", "RET de chdir(var_path)", ret);
	free(var_path);
	if (ret != 0)
	{
		printf("%s %s: ", BOLD RED "minishell:" RESET, g->token->content);
		printf("%s: %s\n", g->token->next->content, strerror(errno));
		return (EXIT_FAILURE);
	}
	return (ret);
}

static void	__replace_or_add_to_env(char ***env, char *var, char *var_path)
{
	char	**new_env = NULL;
	char	*new_var = NULL;
	int		i;
	int		len;

	len = ft_strlen(var);
	i = 0;
	new_var = ft_strjoin(var, var_path);
	if (new_var == NULL)
		return ;
	// on parcourt env pour verifier si la var existe deja
	while ((*env)[i] != NULL)
	{
		if (ft_strncmp((*env)[i], var, len) && (*env)[i][len] == '=')
		{
			free((*env)[i]);
			(*env)[i] = new_var;
			return ;
		}
		i++;
	}
	new_env = malloc(sizeof(char *) * (i + 2));
    if (new_env == NULL)
    {
        free(new_var);
        return ;
    }
	// si la var n'existe pas, on l'ajoute dans le nouvel env
	i = 0;
	while ((*env)[i] != NULL)
	{
		new_env[i] = (*env)[i];
		i++;
	}
	new_env[i] = new_var;
	new_env[i + 1] = NULL;
	free(*env);
	*env = new_env;
}

static void	__update_env_paths(t_global *g)
{
	char	cwd[PATH_MAX];
	char	*old_pwd;

	// valeur actuelle de PWD
	old_pwd = getenv("PWD");
	printf("%s: %s\n", "RET de getenv de PWD pour old_pwd", old_pwd);
	if (getcwd(cwd, sizeof(cwd)) == NULL)
	{
		printf("%s %s: ", BOLD RED "minishell:", RESET "getcwd"); 
		printf("%s\n", strerror(errno));
		return ;
	}
	// maj de OLDPWD
	if (old_pwd != NULL)
		__replace_or_add_to_env(&(g->env), "OLDPWD", old_pwd);
	// maj de PWD avec le nouveau working directory
	__replace_or_add_to_env(&(g->env), "PWD", cwd);
}

int	my_cd(t_token *t, t_global *g)
{
	int	ret;
	
	if (t->next == NULL)
		ret = __cd_to_env_var(g, "HOME=");
	else if (ft_strcmp((const char *)t->next, "-") == 0)
		ret = __cd_to_env_var(g, "OLDPWD=");
	else
	{
		ret = chdir((const char *)t->next);
		printf("%s\n", (const char *)t->next);
	}
	if (ret != 0)
	{
		printf("%s %s: ", BOLD RED "minishell:" RESET, t->content);
		printf("%s: %s\n", t->next->content, strerror(errno));
		return (EXIT_FAILURE);
	}
	__update_env_paths(g);
	// maj de PWD et OLDPWD dans l'env
	return (EXIT_SUCCESS);
}
