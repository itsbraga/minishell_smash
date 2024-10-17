/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: annabrag <annabrag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 16:42:29 by annabrag          #+#    #+#             */
/*   Updated: 2024/10/17 17:40:34 by annabrag         ###   ########.fr       */
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
	// char	*rb_bar;

	// rb_bar = rainbow_prompt(PROMPT_BAR);
	// secure_malloc(rb_bar);
	// pr->header = ft_strjoin(rb_bar, "[");
	// secure_malloc(pr->header);
	// free(rb_bar);
	pr->colored_user = ft_strjoin("\001" BRIGHT_YELLOW "\002", pr->username);
	secure_malloc(pr->colored_user);
	// pr->part1 = ft_strjoin(pr->header, pr->colored_user);
	pr->part1 = ft_strjoin("[", pr->colored_user);
	secure_malloc(pr->part1);
	// free(pr->header);
	free(pr->colored_user);
	pr->colored_42 = ft_strjoin("\001" RED "\002", "42");
	secure_malloc(pr->colored_42);
	pr->tmp = ft_strjoin("\001" R "\002" "@", pr->colored_42);
	secure_malloc(pr->tmp);
	free(pr->colored_42);
}

// static void	__custom_cwd(t_prompt *pr)
// {
// 	char	cwd[PATH_MAX];
// 	char	*tmp;

// 	if (getcwd(cwd, sizeof(cwd)) == NULL)
// 	{
// 		err_msg("0: getcwd() failed", "No such file or directory", 0);
// 		return ;
// 	}
// 	tmp = ft_substr(cwd, 14, (ft_strlen(cwd) - 14));
// 	secure_malloc(tmp);
// 	pr->ccwd = ft_strjoin("\001" "🗿" "\002", tmp);
// 	secure_malloc(pr->ccwd);
// 	free(tmp);
// }

char	*generate_prompt(t_prompt *pr)
{
	char	cwd[PATH_MAX];

	pr->username = getenv("USER");
	if (pr->username == NULL)
		pr->username = "unknown";
	if (getcwd(cwd, sizeof(cwd)) == NULL)
		err_msg("0: getcwd() failed", ERR_BAD_FILE, 0);
	__part_one(pr);
	pr->part2 = ft_strjoin(pr->tmp, "\001" R "\002" "] ");
	secure_malloc(pr->part2);
	free(pr->tmp);
	// __custom_cwd(pr);
	// pr->part3 = ft_strjoin(pr->part2, pr->ccwd);
	pr->part3 = ft_strjoin(pr->part2, cwd);
	secure_malloc(pr->part3);
	free(pr->part2);
	free(pr->ccwd);
	pr->part4 = ft_strjoin(pr->part3, " $> ");
	secure_malloc(pr->part4);
	free(pr->part3);
	pr->prompt = ft_strjoin(pr->part1, pr->part4);
	secure_malloc(pr->prompt);
	(void)yama(ADD, pr->prompt, 0);
	free(pr->part1);
	free(pr->part4);
	return (pr->prompt);
}
