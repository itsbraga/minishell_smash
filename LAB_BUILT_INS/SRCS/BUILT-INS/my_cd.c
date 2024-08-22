/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: annabrag <annabrag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 15:41:26 by annabrag          #+#    #+#             */
/*   Updated: 2024/08/22 17:21:46 by annabrag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "built_ins.h"

static char	*__update_pwd(t_env *env, char **old_pwd)
{
	t_env	*head;
	char	*new_pwd;

	if ((new_pwd = getcwd(NULL, 0)) == NULL)
	{
		printf("%s %s\n", BOLD RED "minishell:" RESET, strerror(errno));
		return (NULL);
	}
	head = env;
	while (head != NULL)
	{
		if (ft_strncmp(head->content, "PWD=", 4) == 0)
		{
			*old_pwd = ft_strdup(head->content);
			free(head->content);
			if ((head->content = ft_strjoin("PWD=", new_pwd)) == NULL)
			{
				printf("%s %s\n", BOLD RED "minishell:" RESET, strerror(errno));
				free(new_pwd);
				return (NULL);
			}
		}
		head = head->next;
	}
	return (new_pwd);
}

static void	__update_oldpwd(t_env *env, char *old_pwd)
{
	t_env	*head;

	head = env;
	while (head != NULL)
	{
		if (ft_strncmp(head->content, "OLDPWD=", 7) == 0 && old_pwd != NULL)
		{
			free(head->content);
			head->content = ft_strjoin("OLDPWD=", old_pwd + 4); // +4 pour ignorer PWD=
			free(old_pwd);
			old_pwd = NULL;
			break ;
		}
		head = head->next;
	}
	if (old_pwd != NULL)
		free(old_pwd);
}

static void	__change_paths(t_env *env)
{
	char	*old_pwd;
	char	*new_pwd;

	old_pwd = NULL;
	new_pwd = __update_pwd(env, &old_pwd);
	if (new_pwd == NULL)
		return ;
	__update_oldpwd(env, old_pwd);
	free(new_pwd);
}

/*	The tilde character (“~”) has a special meaning.
	When used at the beginning of a word, it expands
	into the name of the home directory of the named
	user, or if no user is named, the home directory
	of the current user
	
	>> bonus wildcards
*/
int	my_cd(t_global *g)
{
	int	ret;
	
	if ((g->token->next == NULL)
		|| (ft_strcmp((const char *)g->token->next->content, "~") == 0))
		ret = go_to_env_var(g, "HOME=");
	else if (ft_strcmp((const char *)g->token->next->content, "-") == 0)
		ret = go_to_env_var(g, "OLDPWD=");
	else
		ret = chdir((const char *)g->token->next->content);
	if (ret != 0)
	{
		printf("%s %s: ", BOLD RED "minishell:" RESET, g->token->content);
		printf("%s: %s\n", g->token->next->content, strerror(errno));
		return (EXIT_FAILURE);
	}
	__change_paths(g->env);
	return (EXIT_SUCCESS);
}
