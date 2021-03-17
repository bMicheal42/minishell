/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmeizo <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/28 12:35:31 by tmeizo            #+#    #+#             */
/*   Updated: 2021/03/12 14:46:37 by bmicheal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char	*udst;
	unsigned char	*usrc;

	if (!dst && !src)
		return (0);
	udst = (unsigned char *)dst;
	usrc = (unsigned char *)src;
	if (dst < src)
		while (len--)
			*udst++ = *usrc++;
	else
	{
		udst += len;
		usrc += len;
		while (len--)
			*--udst = *--usrc;
	}
	return (dst);
}
