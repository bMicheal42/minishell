/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmeizo <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/29 15:40:05 by tmeizo            #+#    #+#             */
/*   Updated: 2021/03/12 14:46:37 by bmicheal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

static int		count_strings(const char *s, char c)
{
	int		ret;

	ret = 0;
	while (*s && *s == c)
		s++;
	if (!(*s))
		return (0);
	while (*s)
	{
		if (*s == c)
		{
			while (*s == c)
				s++;
			if (*s)
				ret++;
			continue ;
		}
		s++;
	}
	return (ret + 1);
}

static char		*get_next(const char *s, char c)
{
	char	*ret;
	int		ret_len;
	int		i;

	ret_len = 0;
	while (s[ret_len] && s[ret_len] != c)
		ret_len++;
	if (!(ret = malloc(ret_len + 1)))
		return (0);
	i = 0;
	while (i < ret_len)
	{
		ret[i] = s[i];
		i++;
	}
	ret[i] = 0;
	return (ret);
}

static void		cleanup(char **ret, int i)
{
	while (i--)
	{
		free(ret[i]);
		ret[i] = 0;
	}
	free(ret);
}

static char		**get_words(const char *s, char c, int size)
{
	char	**ret;
	int		i;

	if (!(ret = (char **)malloc(sizeof(char *) * (size + 1))))
		return (0);
	i = -1;
	while (++i < size)
	{
		if (!(ret[i] = get_next(s, c)))
		{
			cleanup(ret, i);
			return (0);
		}
		s += ft_strlen(ret[i]);
		while (*s && *s == c)
			s++;
	}
	ret[i] = 0;
	return (ret);
}

char			**ft_split(const char *s, char c)
{
	int		ret_len;

	if (!s)
		return (0);
	while (*s && *s == c)
		s++;
	ret_len = count_strings(s, c);
	if (ret_len < 0)
		return (0);
	return (get_words(s, c, ret_len));
}
