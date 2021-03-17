/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmeizo <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/30 11:48:06 by tmeizo            #+#    #+#             */
/*   Updated: 2021/03/12 14:46:37 by bmicheal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

static int	get_len(int n)
{
	int	ret;

	if (n == 0)
		return (1);
	ret = 0;
	while (n)
	{
		ret++;
		n /= 10;
	}
	return (ret);
}

char		*ft_itoa(int n)
{
	int		len;
	int		i;
	char	*ret;
	int		sign;

	len = get_len(n);
	sign = 1;
	if (n < 0)
	{
		len++;
		sign = -1;
	}
	ret = malloc(len + 1);
	if (!ret)
		return (0);
	if (n < 0)
		ret[0] = '-';
	i = n < 0 ? 1 : 0;
	ret[len] = 0;
	while (--len >= i)
	{
		ret[len] = ((n % 10) * sign) + '0';
		n /= 10;
	}
	return (ret);
}
