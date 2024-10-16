/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: annabrag <annabrag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 21:37:10 by pmateo            #+#    #+#             */
/*   Updated: 2024/09/20 14:54:04 by annabrag         ###   ########.fr       */
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
	pr->header = ft_strjoin(rainbow_prompt(PROMPT_BAR), "[");
	secure_malloc(pr->header);
	pr->colored_user = ft_strjoin("\001" BRIGHT_YELLOW "\002", pr->username);
	secure_malloc(pr->colored_user);
	pr->part1 = ft_strjoin(pr->header, pr->colored_user);
	secure_malloc(pr->part1);
	free(pr->header);
	free(pr->colored_user);
	pr->colored_42 = ft_strjoin("\001" RED "\002", "42");
	secure_malloc(pr->colored_42);
	pr->tmp = ft_strjoin("\001" R "\002" "@", pr->colored_42);
	secure_malloc(pr->tmp);
	free(pr->colored_42);
}

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
	pr->part3 = ft_strjoin(pr->part2, cwd);
	secure_malloc(pr->part3);
	free(pr->part2);
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

// singleton version
t_data	*data_struct(void)
{
	static t_data	*instance = NULL;
	t_prompt		pr;

	if (instance == NULL)
	{
		instance = yama(CREATE, NULL, sizeof(t_data));
		secure_malloc(instance);
		instance->prompt = generate_prompt(&pr);
		secure_malloc(instance->prompt);
		instance->main = NULL;
		instance->token = NULL;
		instance->exec = NULL;
		instance->info = NULL;
		instance->env = NULL;
		instance->exp_env = NULL;
		instance->last_exit_status = 0;
	}
	return (instance);
}
