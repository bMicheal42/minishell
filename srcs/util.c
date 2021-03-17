/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmeizo <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/21 13:27:15 by tmeizo            #+#    #+#             */
/*   Updated: 2021/03/12 14:46:35 by bmicheal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int		index_of(const char *s, char c)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (c == s[i])
			return (i);
		i++;
	}
	return (-1);
}

char	**copy_split(char **s)
{
	int		i;
	char	**ret;

	i = 0;
	while (s[i])
		i++;
	if (!(ret = malloc(sizeof(char *) * (i + 1))))
		ft_error_list(3);
	ret[i] = 0;
	while (i--)
		ret[i] = ft_strdup(s[i]);
	return (ret);
}

char	**free_split(char **s)
{
	int	i;

	i = 0;
	if (s)
		while (s[i])
			free(s[i++]);
	free(s);
	return (0);
}

void	print_greeting(void)
{
	ft_putstr_fd("\e[1m\e[32m~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\
~~~~~~~~\n\
|\e[0m~~~~~ Welcome to ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\e[1m\e[32m|\n\
|\e[0m~~~~  \e[1m\e[32m______            ____  ___   _____ __  __|\n\
|\e[0m~~~  \e[1m\e[32m/ ____/\e[0m_  __      \e[1m\e[32m/ __ )/   | / ___// / \
/ /|\n\
|\e[0m~~  \e[1m\e[32m/ __/ \e[0m/ (_) /____ \e[1m\e[32m/ __  / /| | \\__ \\/ /_\
/ / |\n\
|\e[0m~  \e[1m\e[32m/ /___\e[0m/ / / __/ -_) \e[1m\e[32m/_/ / ___ |___/ / __  \
/ \e[0m~\e[1m\e[32m|\n\
|\e[0m  \e[1m\e[32m/_____/\e[0m_/_/\\__/\\__\e[1m\e[32m/_____/_/  |_/____/_/ /_\
/ \e[0m~~\e[1m\e[32m|\n\
|\e[0m~~~~~~~~~~~~~~~~~~~~ by tmeizo & bmicheal ~~~~~~\e[1m\e[32m|\n\
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\e[0m\n", 2);
}
