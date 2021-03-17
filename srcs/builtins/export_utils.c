/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmicheal <bmicheal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/04 14:53:42 by bmicheal          #+#    #+#             */
/*   Updated: 2021/03/12 14:46:35 by bmicheal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	export_error(char *s)
{
	ft_putstr_fd("ebash: export: '", 2);
	ft_putstr_fd(s, 2);
	ft_putendl_fd("': not a valid identifier", 2);
}

void	print_sorted_env(char **sorted_envp, int fd, int i, int k)
{
	write(fd, "\"", 1);
	ft_putstr_fd(sorted_envp[k] + i, fd);
	write(fd, "\"", 1);
}

int		env_len(char **envp, char *s, int name_len, int *repl)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], s, name_len) == 0)
			*repl = 1;
		i++;
	}
	return (*repl ? i : i + 1);
}
