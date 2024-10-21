/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: art3mis <art3mis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 16:42:29 by annabrag          #+#    #+#             */
/*   Updated: 2024/10/21 00:11:14 by art3mis          ###   ########.fr       */
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
static void	__part_one(t_prompt *pr)
{
	pr->rainbow_user = rainbow_prompt(pr->username);
	secure_malloc(pr->rainbow_user, true);
	pr->part1 = ft_strjoin("[", pr->rainbow_user);
	secure_malloc(pr->part1, true);
	(void)yama(REMOVE, pr->rainbow_user, 0);
	pr->part2 = ft_strjoin(pr->part1, "\001" R "@42] " "\002");
	secure_malloc(pr->part2, true);
	free(pr->part1);
}

static void	__custom_cwd(t_prompt *pr)
{
	char	cwd[PATH_MAX];
	char	*extracted;
	char	*relative_cwd;

	if (getcwd(cwd, sizeof(cwd)) == NULL)
		return (err_msg("0: getcwd() failed", ERR_BAD_FILE, 0));
	extracted = ft_substr(cwd, 14, (ft_strlen(cwd) - 14));
	secure_malloc(extracted, true);
	relative_cwd = ft_strjoin("~/", extracted);
	secure_malloc(relative_cwd, true);
	free(extracted);
	pr->custom_cwd = ft_strjoin("\001" ITAL LIGHT_GRAY "\002", relative_cwd);
	secure_malloc(pr->custom_cwd, true);
	free(relative_cwd);
}

char	*generate_prompt(t_prompt *pr)
{
	pr->username = getenv("USER");
	if (pr->username == NULL)
		pr->username = "unknown";
	__part_one(pr);
	__custom_cwd(pr);
	pr->part3 = ft_strjoin(pr->part2, pr->custom_cwd);
	secure_malloc(pr->part3, true);
	free(pr->part2);
	free(pr->custom_cwd);
	pr->prompt = ft_strjoin(pr->part3, "\001" R "\002" "\n$> ");
	secure_malloc(pr->prompt, true);
	(void)yama(ADD, pr->prompt, 0);
	free(pr->part3);
	return (pr->prompt);
}

void	update_prompt(t_data *d, t_prompt *pr)
{
	if (d->prompt != NULL)
	{
		(void)yama(REMOVE, d->prompt, 0);
		d->prompt = NULL;
	}
	d->prompt = generate_prompt(pr);
	secure_malloc(d->prompt, true);
}
