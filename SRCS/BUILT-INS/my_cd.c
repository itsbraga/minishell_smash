/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmateo <pmateo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 15:41:26 by annabrag          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2024/08/26 16:56:08 by annabrag         ###   ########.fr       */
=======
<<<<<<< HEAD
/*   Updated: 2024/08/26 16:12:32 by pmateo           ###   ########.fr       */
=======
/*   Updated: 2024/08/26 15:06:06 by annabrag         ###   ########.fr       */
>>>>>>> 6e6a8733545fee32380e072c25f1579acc0c37b4
>>>>>>> 331b04d903f2a2b001b4dd4fcb2fdae6e653d3e1
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*__update_pwd(t_env *env, char **old_pwd)
{
	t_env	*head;
	char	*new_pwd;

	new_pwd = getcwd(NULL, 0);
	if (new_pwd == NULL)
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
				return (free(new_pwd), NULL);
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
		errmsg_status(g->token->content, g->token->next->content, errno);
	__change_paths(g->env);
	return (SUCCESS);
}
