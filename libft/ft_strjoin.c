/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmeizo <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/29 15:12:59 by tmeizo            #+#    #+#             */
/*   Updated: 2021/03/12 14:46:37 by bmicheal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

char	*ft_strjoin(const char *a, const char *b)
{
	size_t	a_len;
	size_t	i;
	char	*ret;

	if (!a || !b)
		return (0);
	a_len = ft_strlen(a);
	ret = malloc(a_len + ft_strlen(b) + 1);
	if (!ret)
		return (0);
	i = 0;
	while (a[i])
	{
		ret[i] = a[i];
		i++;
	}
	while (b[i - a_len])
	{
		ret[i] = b[i - a_len];
		i++;
	}
	ret[i] = 0;
	return (ret);
}
