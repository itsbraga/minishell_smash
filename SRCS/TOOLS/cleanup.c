/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: art3mis <art3mis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 17:53:27 by annabrag          #+#    #+#             */
/*   Updated: 2024/10/22 23:30:33 by art3mis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tools.h"

void	clean_after_execution(t_data *d, char *user_input)
{
	lstclear_main(&(d->main));
	lstclear_token(&(d->token));
	lstclear_exec(&(d->exec));
	free_and_set_null(user_input);
}

void	free_tab(char **tab)
{
	int	i;

	if (tab == NULL)
		return ;
	i = 0;
	while (tab[i] != NULL)
	{
		free_and_set_null(tab[i]);
		i++;
	}
	free_and_set_null(tab);
}

int	free_gc_tab(t_gc_lst **yama, char **tab)
{
	int	error;
	int	i;

	error = 0;
	i = 0;
	// dprintf(2, "free_gc_tab\n");
	// print_tab2(tab);
	while (tab[i] != NULL)
	{
		// dprintf(2, "free_gc_tab | i = %d\n", i);
		error = remove_gc_node(yama, tab[i]);
		i++;
	}
	// dprintf(2, "free_gc_tab = %p\n", tab);
	remove_gc_node(yama, tab);
	return (error);
}

static void	__free_data(t_data *d, bool clear_history)
{
	if (d != NULL)
	{
		if (d->prompt != NULL)
			free_and_set_null(d->prompt);
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
		free(d);
	}
}

void	clean_exit_shell(int err_status)
{
	t_data	*d;

	d = data_struct();
	if (d != NULL)
		__free_data(d, true);
	yama(CLEAN_ALL, NULL, 0);
	printf("%s\n", BOLD BLUE BYE_MSG R);
	exit(err_status); // verifier si on ne doit pas plutot quitter avec last_exit_code
}
