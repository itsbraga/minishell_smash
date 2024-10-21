/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   additionnal.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: art3mis <art3mis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/20 20:02:37 by art3mis           #+#    #+#             */
/*   Updated: 2024/10/20 22:04:28 by art3mis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gc.h"

void	clean_exit_shell(int err_status)
{
	yama(CLEAN_ALL, NULL, 0);
	exit(err_status);
}

void	secure_malloc(void *to_secure)
{
	if (to_secure == NULL)
	{
		err_msg("malloc", ERR_MALLOC, 0);
		clean_exit_shell(FAILURE);
	}
}

static char	*__append_strs(char *s1, char *s2)
{
	char	*tmp;

	if (s2 == NULL)
		return (s1);
	if (s1 == NULL)
		return (ft_strdup(s2));
	tmp = s1;
	s1 = ft_strjoin(tmp, s2);
	secure_malloc(s1);
	(void)yama(ADD, s1, 0);
	free(tmp);
	tmp = NULL;
	return (s1);
}

void	err_msg(char *detail, char *reason, int quotes)
{
	char	*msg;

	msg = NULL;
	if (detail != NULL)
	{
		if (quotes == 1)
		{
			msg = __append_strs(__append_strs(NULL, ERR_PREFIX), "‘");
			msg = __append_strs(__append_strs(msg, detail), "’");
		}
		else
			msg = __append_strs(__append_strs(NULL, ERR_PREFIX), detail);
		msg = __append_strs(msg, ": ");
		msg = __append_strs(msg, reason);
	}
	else if (quotes == 2)
	{
		msg = __append_strs(__append_strs(NULL, ERR_PREFIX), ERR_PIPE);
		msg = __append_strs(__append_strs(msg, reason), "'");
	}
	else
		msg = __append_strs(__append_strs(NULL, ERR_PREFIX), reason);
	printf("%s\n", msg);
	yama(REMOVE, msg, 0);
	msg = NULL;
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char			*join;
	unsigned int	s1_len;
	unsigned int	s2_len;

	if (!s1 || !s2)
		return (NULL);
	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	join = malloc(sizeof(char) * (s1_len + s2_len + 1));
	if (!join)
		return (NULL);
	ft_memcpy(join, s1, s1_len);
	ft_memcpy(join + s1_len, s2, s2_len);
	join[s1_len + s2_len] = '\0';
	return (join);
}

char	*ft_strdup(const char *s1)
{
	size_t	size;
	char	*s2;

	size = ft_strlen(s1) + 1;
	s2 = malloc(size * sizeof(char));
	if (s2 == NULL)
		return (NULL);
	ft_strlcpy(s2, s1, size);
	return (s2);
}
