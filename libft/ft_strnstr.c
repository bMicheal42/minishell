/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmeizo <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/28 17:30:37 by tmeizo            #+#    #+#             */
/*   Updated: 2021/03/12 14:46:37 by bmicheal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	iseq(const char *a, const char *b)
{
	int	i;

	i = -1;
	while (a[++i] && b[i])
		if (a[i] != b[i])
			return (0);
	return (1);
}

char		*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	needle_len;

	needle_len = ft_strlen(needle);
	if (!needle_len)
		return ((char *)haystack);
	if (needle_len > ft_strlen(haystack) || len < needle_len)
		return (0);
	i = -1;
	while (haystack[++i] && i <= len - needle_len)
		if (iseq(haystack + i, needle))
			return ((char *)haystack + i);
	return (0);
}
