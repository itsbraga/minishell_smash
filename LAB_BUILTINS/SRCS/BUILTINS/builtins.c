/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: annabrag <annabrag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 16:20:34 by annabrag          #+#    #+#             */
/*   Updated: 2024/09/06 17:59:33 by annabrag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "my_builtins.h"

// bool	is_built_in(char *cmd)
// {
// 	int			i;
// 	const char	*built_in[] =
// 	{
// 		"pwd",
// 		"cd",
// 		"env",
// 		"exit"
// 	};

// 	i = 0;
// 	while (built_in[i] != NULL)
// 	{
// 		if (ft_strcmp(built_in[i++], cmd) == 0)
// 			return (true);
// 	}
// 	return (false);
// }

void	exec_built_in(char **built_in, t_global *g)
{
	if (ft_strcmp(built_in[0], "pwd") == 0)
		my_pwd();
	else if (ft_strcmp(built_in[0], "cd") == 0)
		my_cd(g);
	else if (ft_strcmp(built_in[0], "env") == 0)
	{
		if (built_in[1] != NULL)
			return (err_msg(built_in[1], "No such file or directory"));
		my_env(g->env);
	}
	else if (ft_strcmp(built_in[0], "exit") == 0)
		my_exit(g, built_in);
	else if (ft_strcmp(built_in[0], "unset") == 0)
		my_unset(g, built_in + 1);
	else if (ft_strcmp(built_in[0], "clear") == 0)
		printf("\033[H\033[J");
}
//shlvl a update

// certain builtin peuvent agir differement avec des parametres
// (genre env 1 doit pas afficher l'env mais un message d'erreur)
// a voir si vous le faite le sujet est vague dessus 								EN COURS (LEAK)

// cd seul : va dans home 															OK

// old_pwd doit ce mettre a jour avec un "cd ." 									OK

// exit avec des parametres pas numeriques affiche des messages
// d'erreurs (je crois que c'est des messages differents en
// fonctions du parametre genre char, string, num negatif, ...) 					EN COURS (LEAK)

// leak exit

// unset a tester avec export