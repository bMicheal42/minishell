/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_util.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmeizo <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/22 15:04:53 by tmeizo            #+#    #+#             */
/*   Updated: 2021/03/12 14:46:37 by bmicheal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int		cmp_name(char *a, char *b)
{
	while (*a && *a != '=' && *b)
		if (*a++ != *b++)
			return (0);
	if (*a == '=' && !*b)
		return (1);
	return (0);
}

char	*ft_getenv(char *name, char **envp)
{
	int	i;

	i = 0;
	while (*envp)
	{
		if (cmp_name(*envp, name))
		{
			while ((*envp)[i] != '=')
				i++;
			return (*envp + ++i);
		}
		envp++;
	}
	return ("");
}
