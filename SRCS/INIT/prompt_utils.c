/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: annabrag <annabrag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 02:40:19 by art3mis           #+#    #+#             */
/*   Updated: 2024/11/04 19:10:25 by annabrag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*	Readline should not count escape sequences as visible characters.
	This is achieved by encapsulating the non-visible parts (escape
	sequences) of the prompt between special sequences :
	
	-	\001 (start of non-visible sequence)
	-	\002 (end of non-visible sequence)
	
	This enables readline to manage the length of the prompt correctly.
*/
void	part_one(t_prompt *pr)
{
	pr->user = ft_strjoin("\001" BR "\002", pr->username);
	secure_malloc(pr->user, true);
	pr->part1 = ft_strjoin("\001" BOLD "[" "\002", pr->user);
	secure_malloc(pr->part1, true);
	free_and_set_null((void **)&pr->user);
	pr->part2 = ft_strjoin(pr->part1, "\001" R BOLD "@" PY "42" R BOLD "] "\
	R "\002");
	secure_malloc(pr->part2, true);
	free_and_set_null((void **)&pr->part1);
}

void	custom_cwd(t_prompt *pr)
{
	char	*path;
	char	*add_tild;
	char	*tmp;

	path = substract_path(pr);
	secure_malloc(path, true);
	add_tild = ft_strjoin("~", path);
	secure_malloc(add_tild, true);
	free_and_set_null((void **)&path);
	tmp = ft_strjoin("\001" ITAL LIGHT_GRAY2 "\002", add_tild);
	secure_malloc(tmp, true);
	free_and_set_null((void **)&add_tild);
	pr->custom_cwd = ft_strjoin(tmp, "\001" R "\002");
	secure_malloc(pr->custom_cwd, true);
	free_and_set_null((void **)&tmp);
}

char	*substract_path(t_prompt *pr)
{
	char	cwd[PATH_MAX];

	if (getcwd(cwd, sizeof(cwd)) == NULL)
	{
		err_msg("0: getcwd() failed", ERR_BAD_FILE, 0);
		return (NULL);
	}
	pr->home_path = getenv("HOME");
	if (pr->home_path == NULL)
		pr->extracted = ft_strdup(cwd);
	else
	{
		pr->home_pos = ft_strnstr(cwd, pr->home_path, ft_strlen(cwd));
		if (pr->home_pos == NULL)
			pr->extracted = ft_strdup(cwd);
		else
			pr->extracted = ft_strdup(pr->home_pos + ft_strlen(pr->home_path));
	}
	secure_malloc(pr->extracted, true);
	return (pr->extracted);
}
