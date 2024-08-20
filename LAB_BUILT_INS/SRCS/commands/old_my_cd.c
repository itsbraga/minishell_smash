/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   old_my_cd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: annabrag <annabrag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 15:41:26 by annabrag          #+#    #+#             */
/*   Updated: 2024/08/20 19:37:08 by annabrag         ###   ########.fr       */
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
	printf("%s %s\n", BOLD BLUE "PATH:" RESET, var_path);
	ret = chdir((const char *)var_path);
	printf("%s %d\n", BOLD YELLOW "1. RETURN de chdir:" RESET, ret);
	if (ret != 0)
	{
		printf("%s %s: ", BOLD RED "minishell:" RESET, g->token->content);
		printf("%s: %s\n", g->token->next->content, strerror(errno));
		return (EXIT_FAILURE);
	}
	if (var_path != NULL)
		free(var_path);
	return (ret);
}

// static void	__update_env_paths(void)
// {
// 	char	cwd[PATH_MAX];
// 	char	*old_pwd;

// 	// valeur actuelle de PWD
// 	old_pwd = getenv("PWD");
// 	if (getcwd(cwd, sizeof(cwd)) == NULL)
// 	{
// 		printf("%s %s: ", BOLD RED "minishell:", RESET "getcwd"); 
// 		printf("%s\n", strerror(errno));
// 		return ;
// 	}
// 	// maj de OLDPWD
// 	// maj de PWD avec le nouveau working directory
// }

int	my_cd(t_global *g)
{
	int	ret;
	
	if (g->token->next == NULL)
		ret = __cd_to_env_var(g, "HOME=");
	else if (ft_strcmp((const char *)g->token->next->content, "-") == 0)
		ret = __cd_to_env_var(g, "OLDPWD=");
	else
	{
		ret = chdir((const char *)g->token->next->content);
		printf("%s %d\n", BOLD BLUE "2. RETURN de chdir:" RESET, ret);
	}
	if (ret != 0)
	{
		printf("%s %s: ", BOLD RED "minishell:" RESET, g->token->content);
		printf("%s: %s\n", g->token->next->content, strerror(errno));
		return (EXIT_FAILURE);
	}
	// __update_env_paths();
	return (EXIT_SUCCESS);
}
