/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmeizo <tmeizo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/19 09:53:48 by tmeizo            #+#    #+#             */
/*   Updated: 2021/03/12 14:46:37 by bmicheal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strcmp(const char *a, const char *b)
{
	size_t			i;
	unsigned char	*ua;
	unsigned char	*ub;

	ua = (unsigned char *)a;
	ub = (unsigned char *)b;
	i = 0;
	while (ua[i] && ub[i])
	{
		if (ua[i] != ub[i])
			return (ua[i] - ub[i]);
		i++;
	}
	return (ua[i] - ub[i]);
}
