/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmeizo <tmeizo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/19 09:45:08 by tmeizo            #+#    #+#             */
/*   Updated: 2021/03/12 14:46:37 by bmicheal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	check_n(char *s)
{
	if (*s++ == '-' && *s == 'n')
	{
		while (*s)
			if (*s++ != 'n')
				return (0);
		return (1);
	}
	return (0);
}

int			echo(char **argv, int fd)
{
	size_t	i;
	int		endl;

	i = 1;
	endl = 0;
	while (argv[i] && check_n(argv[i]) && (endl = 1))
		i++;
	while (argv[i])
	{
		ft_putstr_fd(argv[i], fd);
		if (argv[++i])
			write(fd, " ", 1);
	}
	write(fd, "\n", endl ? 0 : 1);
	return (0);
}
