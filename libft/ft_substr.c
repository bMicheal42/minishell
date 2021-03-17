/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmeizo <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/29 13:26:12 by tmeizo            #+#    #+#             */
/*   Updated: 2021/03/12 14:46:37 by bmicheal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

static int	ft_min(size_t a, size_t b)
{
	return (a < b ? a : b);
}

char		*ft_substr(const char *s, unsigned int start, size_t len)
{
	char	*ret;
	size_t	s_len;
	size_t	i;

	if (!s)
		return (0);
	s_len = ft_strlen(s);
	ret = malloc((start < s_len ? ft_min(len, s_len - start) : 0) + 1);
	if (!ret)
		return (0);
	i = start;
	while (i < s_len && i - start < len)
	{
		ret[i - start] = s[i];
		i++;
	}
	ret[i - start] = 0;
	return (ret);
}
