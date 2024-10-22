/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmateo <pmateo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 17:53:27 by annabrag          #+#    #+#             */
/*   Updated: 2024/10/23 00:18:19 by pmateo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	secure_malloc(void *to_secure, bool cleanup)
{
	if (to_secure == NULL)
	{
		err_msg("malloc", strerror(errno), 0);
		if (cleanup == true)
			clean_exit_shell(FAILURE); // de meme pour le code ici (cf. en bas)
	}
}

void	free_tab(char **tab)
{
	int	i;

	if (tab == NULL)
		return ;
	i = 0;
	while (tab[i] != NULL)
	{
		free(tab[i]);
		tab[i] = NULL;
		i++;
	}
	free(tab);
	tab = NULL;
}

int	free_gc_tab(t_gc_lst **y, char **tab)
{
	int	error;
	int	i;

	error = 0;
	i = 0;
	// dprintf(2, "free_gc_tab\n");
	// print_tab2(tab);
	// if (yama(SEARCH, tab, 0) == NULL)
	// 	dprintf(2, "free_gc_tab | tab n'est pas présent dans yama\n");
	// else
	// 	dprintf(2, "free_gc_tab | tab est présent dans yama\n");
	while (tab[i] != NULL)
	{
		// dprintf(2, "free_gc_tab | i = %d\n", i);
		// if (yama(SEARCH, tab[i], 0) == NULL)
		// 	dprintf(2, "free_gc_tab | tab[%d] n'est pas présent dans yama\n", i);
		// else
		// 	dprintf(2, "free_gc_tab | tab[%d] est présent dans yama\n", i);
		// dprintf(2, "free_gc_tab | error = %d\n", error);
		error = remove_gc_node(y, tab[i]);
		i++;
	}
	// dprintf(2, "free_gc_tab = %p\n", tab);
	remove_gc_node(y, tab);
	return (error);
}

static void	__free_data(t_data *d, bool clear_history)
{
	if (d != NULL)
	{
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
