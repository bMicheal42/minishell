/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmeizo <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/30 12:29:48 by tmeizo            #+#    #+#             */
/*   Updated: 2021/03/12 14:46:37 by bmicheal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	arg_n_exit(char *s)
{
	unsigned long long	res;
	int					sign;
	int					i;

	sign = 1;
	res = 0;
	i = 0;
	if (s[i] == '+' || s[i] == '-')
	{
		sign = s[i] == '-' ? -sign : sign;
		i++;
	}
	while (s[i])
	{
		res = res * 10 + (s[i] - '0');
		if (!ft_isdigit(s[i++]) || (res > LONG_MAX && sign == 1) ||
			(res > (unsigned long long)LONG_MAX + 1 && sign == -1))
		{
			ft_putstr_fd("ebash: exit: ", 2);
			ft_putstr_fd(s, 2);
			ft_putendl_fd(": numeric argument required", 2);
			exit(255);
		}
	}
	exit((res * sign) & 0xff);
}

static int	check_arg(char *s)
{
	while (*s == ' ' || (*s >= 9 && *s <= 13))
		s++;
	if (*s == '-' || *s == '+')
		s++;
	while (*s)
		if (!ft_isdigit(*s++))
			return (0);
	return (1);
}

int			ft_exit(char **argv)
{
	char		*s;

	if (!argv[1])
		exit(g_exit_status);
	else if (check_arg(argv[1]) && argv[2])
	{
		ft_putendl_fd("ebash: exit: too many arguments", 2);
		g_exit_status = 1;
		return (1);
	}
	s = argv[1];
	while (*s == ' ' || (*s >= 9 && *s <= 13))
		s++;
	if (!ft_isdigit(*s) && *s != '+' && *s != '-')
	{
		ft_putstr_fd("ebash: exit: ", 2);
		ft_putstr_fd(argv[1], 2);
		ft_putendl_fd(": numeric argument required", 2);
		exit(255);
	}
	arg_n_exit(s);
	return (0);
}
