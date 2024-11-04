/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: art3mis <art3mis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 17:53:27 by annabrag          #+#    #+#             */
/*   Updated: 2024/11/03 23:23:35 by art3mis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tools.h"

void	clean_after_execution(t_data *d, char *input)
{
	g_sig_code = 0;
	close_hd_all_nodes(data_struct());
	if (d->main != NULL)
		lstclear_main(&(d->main));
	if (d->token != NULL)
		lstclear_token(&(d->token));
	if (d->exec != NULL)
		lstclear_exec(&(d->exec));
	if (input != NULL)
		free_and_set_null((void **)&input);
}

void	free_tab(char **tab)
{
	int	i;

	if (tab == NULL)
		return ;
	i = 0;
	while (tab[i] != NULL)
	{
		free_and_set_null((void **)&tab[i]);
		i++;
	}
	free_and_set_null((void **)&tab);
}

int	free_gc_tab(t_gc_lst **y, char **tab)
{
	int	error;
	int	i;

	error = 0;
	i = 0;
	while (tab[i] != NULL)
	{
		error = remove_gc_node(y, tab[i]);
		i++;
	}
	remove_gc_node(y, tab);
	return (error);
}

static void	__free_data(t_data *d, bool clear_history)
{
	if (d != NULL)
	{
		if (d->prompt != NULL)
			free_and_set_null((void **)&(d->prompt));
		if (d->fd_stdin_backup)
			close(d->fd_stdin_backup);
		if (d->main != NULL)
			lstclear_main(&(d->main));
		if (d->token != NULL)
			lstclear_token(&(d->token));
		if (d->exec != NULL)
			lstclear_exec(&(d->exec));
		if (clear_history == true)
		{
			if (d->env != NULL)
				lstclear_env(&(d->env));
			if (d->exp_env != NULL)
				lstclear_env(&(d->exp_env));
			rl_clear_history();
		}
	}
}

void	clean_exit(int err_no)
{
	if (data_struct() != NULL)
		__free_data(data_struct(), true);
	yama(CLEAN_ALL, NULL, 0);
	exit(ft_exit_status(err_no, ADD));
}
