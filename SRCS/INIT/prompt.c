/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: annabrag <annabrag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 16:42:29 by annabrag          #+#    #+#             */
/*   Updated: 2024/11/02 21:29:03 by annabrag         ###   ########.fr       */
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
	free_and_set_null((void **)&pr->part1);
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
	relative_cwd = ft_strjoin("~", extracted);
	secure_malloc(relative_cwd, true);
	free_and_set_null((void **)&extracted);
	pr->custom_cwd = ft_strjoin("\001" ITAL LIGHT_GRAY "\002", relative_cwd);
	secure_malloc(pr->custom_cwd, true);
	free_and_set_null((void **)&relative_cwd);
}

char	*generate_prompt(t_prompt *pr, t_data *d)
{
	pr->username = getenv("USER");
	if (pr->username == NULL)
		pr->username = "unknown";
	__part_one(pr);
	__custom_cwd(pr);
	pr->part3 = ft_strjoin(pr->part2, pr->custom_cwd);
	secure_malloc(pr->part3, true);
	free_and_set_null((void **)&pr->part2);
	free_and_set_null((void **)&pr->custom_cwd);
	d->prompt = ft_strjoin(pr->part3, "\001" R "\002" "\n$> ");
	secure_malloc(d->prompt, true);
	free_and_set_null((void **)&pr->part3);
	return (d->prompt);
}

void	update_prompt(t_data *d, t_prompt *pr)
{
	if (d->prompt != NULL)
		free_and_set_null((void **)&d->prompt);
	d->prompt = generate_prompt(pr, d);
	secure_malloc(d->prompt, true);
}

void	rl_reset_custom_prompt(void)
{
	t_prompt	pr;
	char		*nl_pos;
	size_t		line1_len;

	rl_on_new_line();
	rl_replace_line("", 0);
	update_prompt(data_struct(), &pr);
	nl_pos = ft_strchr(data_struct()->prompt, '\n');
	if (nl_pos != NULL)
	{
		line1_len = nl_pos - data_struct()->prompt + 1;
		write(STDOUT_FILENO, data_struct()->prompt, line1_len);
		rl_redisplay();
	}
}
