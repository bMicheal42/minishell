/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmeizo <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/28 10:12:01 by tmeizo            #+#    #+#             */
/*   Updated: 2021/03/12 14:46:37 by bmicheal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

double	ft_atof(char *s)
{
	double	res;
	double	frac;
	int		sign;
	int		decs;

	res = 0;
	frac = 0;
	sign = 1;
	while (*s && (*s == ' ' || (*s >= 9 && *s <= 13)))
		s++;
	if (*s && (*s == '+' || *s == '-'))
		sign = *s++ == '-' ? -sign : sign;
	while (*s && *s >= '0' && *s <= '9')
		res = res * 10 + *s++ - '0';
	if (*s && *s++ == '.' && (decs = 0) == 0)
	{
		while (*s && *s >= '0' && *s <= '9')
		{
			decs++;
			frac = frac * 10 + *s++ - '0';
		}
		while (decs--)
			frac /= 10;
	}
	return ((res + frac) * sign);
}
