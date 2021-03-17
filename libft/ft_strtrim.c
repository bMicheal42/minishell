/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmeizo <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/29 15:24:35 by tmeizo            #+#    #+#             */
/*   Updated: 2021/03/12 14:46:37 by bmicheal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

static int		has_c(const char *s, const char c)
{
	int i;

	i = -1;
	while (s[++i])
		if (s[i] == c)
			return (1);
	return (0);
}

static size_t	get_len(const char *s, const char *set)
{
	size_t	ret;

	ret = ft_strlen(s);
	if (!ret)
		return (0);
	while (ret && has_c(set, s[ret - 1]))
		ret--;
	while (ret && has_c(set, *s))
	{
		s++;
		ret--;
	}
	return (ret);
}

char			*ft_strtrim(const char *s, const char *set)
{
	size_t	ret_len;
	size_t	i;
	char	*ret;

	if (!s || !set)
		return (0);
	ret_len = get_len(s, set);
	ret = malloc(ret_len + 1);
	if (!ret)
		return (0);
	i = 0;
	while (has_c(set, *s))
		s++;
	while (i < ret_len)
	{
		ret[i] = s[i];
		i++;
	}
	ret[i] = 0;
	return (ret);
}
