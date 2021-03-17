/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmeizo <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/28 16:03:37 by tmeizo            #+#    #+#             */
/*   Updated: 2021/03/12 14:46:37 by bmicheal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	catlen;
	size_t	ret;
	size_t	dst_len;

	dst_len = ft_strlen(dst);
	if (dstsize && dstsize > dst_len)
	{
		catlen = dstsize - dst_len - 1;
		while (*dst)
			dst++;
		ret = dst_len + ft_strlen(src);
		while (catlen-- && *src)
		{
			*dst = *src;
			dst++;
			src++;
		}
		*dst = 0;
	}
	else
		ret = dstsize + ft_strlen(src);
	return (ret);
}
