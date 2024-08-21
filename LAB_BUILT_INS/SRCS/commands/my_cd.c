/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: annabrag <annabrag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 15:41:26 by annabrag          #+#    #+#             */
/*   Updated: 2024/08/21 20:00:19 by annabrag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "built_ins.h"

static char	*__find_var_path(char *to_find, t_env *env)
{
	t_env	*head;
	char	*path;
	int		len_var_env;
	int		len_to_find;

	head = env;
	path = NULL;
	len_to_find = ft_strlen(to_find);
	while (head != NULL)
	{
		len_var_env = ft_strlen(head->content);
		if (ft_strncmp(head->content, to_find, len_to_find) == 0)
		{
			path = ft_substr(head->content, len_to_find,
					(len_var_env - len_to_find));
			return (path);
		}
		head = head->next;
	}
	return (NULL);
}

static int	__go_to_env_var(t_global *g, char *var)
{
	char	*var_path;
	int		ret;

	var_path = __find_var_path(var, g->env);
	printf("%s %s\n", BOLD BLUE "var_path:" RESET, var_path);
	ret = chdir((const char *)var_path);
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

static void	__change_paths(t_env *env)
{
	t_env	*head;
	char	*tmp;
	int		flag;

	head = env;
	flag = 0;
	while (head != NULL)
	{
		if (ft_strncmp(head->content, "PWD=", 4) == 0)
		{
			flag = 1;
			tmp = ft_strdup(head->content);
			free(head->content);
			head->content = NULL;
			head->content = ft_strjoin("PWD=", getcwd(NULL, 0));
			if (head->content == NULL)
			{
				printf("%s %s\n", BOLD RED "minishell:" RESET, strerror(errno));
				return ;
			}
		}
		else if ((ft_strncmp(head->content, "OLDPWD=", 7) == 0) && flag == 1)
		{
			free(head->content);
			head->content = tmp;
		}
		head = head->next;
	}
}

static void	__update_env_paths(t_env *env)
{
	char	cwd[PATH_MAX];
	char	*old_pwd;

	// valeur actuelle de PWD
	old_pwd = getenv("PWD");
	if (getcwd(cwd, sizeof(cwd)) == NULL)
	{
		printf("%s %s: ", BOLD RED "minishell:", RESET "getcwd"); 
		printf("%s\n", strerror(errno));
		return ;
	}
	if (old_pwd != NULL)
		__change_paths(env);
}

int	my_cd(t_global *g)
{
	int	ret;
	
	if (g->token->next == NULL)
		ret = __go_to_env_var(g, "HOME=");
	else if (ft_strcmp((const char *)g->token->next->content, "-") == 0)
		ret = __go_to_env_var(g, "OLDPWD=");
	else
		ret = chdir((const char *)g->token->next->content);
	if (ret != 0)
	{
		printf("%s %s: ", BOLD RED "minishell:" RESET, g->token->content);
		printf("%s: %s\n", g->token->next->content, strerror(errno));
		return (EXIT_FAILURE);
	}
	__update_env_paths(g->env);
	return (EXIT_SUCCESS);
}
