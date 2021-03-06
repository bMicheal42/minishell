/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmeizo <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/26 13:07:05 by tmeizo            #+#    #+#             */
/*   Updated: 2021/03/12 14:46:35 by bmicheal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	env(char **envp, int fd)
{
	int	i;

	while (*envp)
	{
		i = 0;
		while ((*envp)[i] && (*envp)[i] != '=')
			i++;
		if ((*envp)[i + 1])
			ft_putendl_fd(*envp, fd);
		envp++;
	}
	return (0);
}
