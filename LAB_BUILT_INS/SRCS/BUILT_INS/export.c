/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmateo <pmateo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 16:43:03 by annabrag          #+#    #+#             */
/*   Updated: 2024/10/14 22:52:45 by pmateo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "my_builtins.h"

static int	__cmp_to_equal(const char *s1, const char *s2)
{
	int	i;

	i = 0;
	while (s1[i] == s2[i] && s1[i] && s2[i] && s1[i] != '=' && s2[i] != '=')
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

static	void	__add_var_to_exp_env(t_env_lst *e_env, char *var)
{
	t_env_lst	*curr;
	t_env_lst	*new;

	curr = e_env;
	new = env_new_var(var);
	if (__cmp_to_equal(curr->content, new->content) > 0)
	{
		new->next = curr;
		e_env = new;
	}
	else
	{
		while (curr->next != NULL)
		{
			dprintf(2, "add_var_exp\n");
			dprintf(2, "%s\n", curr->content);
			if (__cmp_to_equal(curr->next->content, new->content) > 0)
			{
				new->next = curr->next;
				curr->next = new;
			}
			curr = curr->next;
		}
	}
}

// static	void	__add_var_to_env(t_env_lst *env, char *var)
// {
	
// }

char	*add_quotes_to_value(char *var)
{
	int		i;
	char	*new_str;
	char	*tmp;

	i = 0;
	new_str = malloc((ft_strlen(var) + 3) * sizeof(char));
	if (new_str == NULL)
		exit (FAILURE);
	tmp = var;
	while (*var != '=')
		new_str[i++] = *var++;
	new_str[i++] = *var++;
	new_str[i++] = '"';
	while (*var != '\0')
		new_str[i++] = *var++;
	new_str[i++] = '"';
	new_str[i] = '\0';
	free(tmp);
	return (new_str);
}

static	void	__manage_variable(t_env_lst *exp_env, t_env_lst *env, char *var)
{
	(void)env;
	if (ft_strchr(var, '=') == NULL)
		__add_var_to_exp_env(exp_env, var);
	else
	{
		// __add_var_to_env(env, var);
		// printf("var = %s\n", var);
		var = add_quotes_to_value(var);
		// printf("after add quotes, var = %s\n", var);
		__add_var_to_exp_env(exp_env, var);
	}
	return ;
}

int	check_arg(char *var)
{
	int	i;

	i = 0;
	if (!((var[0] >= 'A' && var[0] <= 'Z')
		|| (var[0] >= 'a' && var[0] <= 'z')
		|| var[i] != '_'))
		return (err_msg_cmd("export", var, ERR_ENV_VAR, FAILURE));
	while (var[i] != '=' && var[i] != '\0')
	{
		// dprintf(2, "check_arg loop\n");
		if ((var[i] >= 'A' && var[i] <= 'Z')
			|| (var[i] >= 'a' && var[i] <= 'z')
			|| (var[i] >= '0' && var[i] <= '9')
			|| (var[i] == '_'))
			i++;
		else
			return (err_msg_cmd("export", var, ERR_ENV_VAR, FAILURE));
	}
	return (SUCCESS);
}

static	void	__print_export_env(t_env_lst *exp_env)
{
	t_env_lst    *curr;

    curr = exp_env;
	while (curr != NULL)
	{
        ft_printf(1, "export ");
		ft_printf(1, "%s\n", curr->content);
        curr = curr->next;
  	}
}

void    my_export(t_env_lst *exp_env, t_env_lst *env, char **args)
{
	unsigned	int	i;
	
	i = 1;
	if (args[1] == NULL)
		__print_export_env(exp_env);
	else
	{
		while (args[i] != NULL)
		{
			dprintf(2, "my export loop\n");
			dprintf(2, "args[i] = %s\n", args[i]);
			if (check_arg(args[i]) == SUCCESS)
				__manage_variable(exp_env, env, args[i]);
			i++;
		}	
	}
}
	
//code de sortie ?
// si ajout de $WAOUH elle doit se glisser apres VTE_VERSION et
//	avant XAUTHORITY