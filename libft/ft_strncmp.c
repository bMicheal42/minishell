/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmeizo <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/29 11:24:26 by tmeizo            #+#    #+#             */
/*   Updated: 2021/03/12 14:46:37 by bmicheal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *a, const char *b, size_t n)
{
	size_t			i;
	unsigned char	*ua;
	unsigned char	*ub;

	ua = (unsigned char *)a;
	ub = (unsigned char *)b;
	i = 0;
	while (i < n && ua[i] && ub[i])
	{
		if (ua[i] != ub[i])
			return (ua[i] - ub[i]);
		i++;
	}
	if (i == n)
		return (0);
	return (ua[i] - ub[i]);
}
