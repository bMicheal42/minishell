/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmeizo <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/26 12:09:06 by tmeizo            #+#    #+#             */
/*   Updated: 2021/03/12 14:46:35 by bmicheal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	**update_env(char **exp_argv, int fd)
{
	char	*cwd;
	char	**new_env;

	cwd = getcwd(0, 0);
	if (!cwd)
	{
		ft_putstr_fd("ebash: error retrieving current directory: getcwd: "
					"cannot access parent directories: ", 2);
		ft_putendl_fd(strerror(errno), 2);
		return (0);
	}
	if (!(exp_argv[1] = ft_strjoin("PWD=", cwd)))
		return (0);
	if (!(new_env = export(exp_argv, g_envp, fd)))
		return (0);
	free_split(exp_argv);
	free(cwd);
	return (new_env);
}

static char	**update_oldpwd(int fd)
{
	char	**new_env;
	char	**exp_argv;
	int		i;

	i = 0;
	if (!(exp_argv = ft_split("export OLDPWD=", ' ')))
		return (0);
	free(exp_argv[1]);
	if (!(exp_argv[1] = ft_strjoin("OLDPWD=", ft_getenv("PWD", g_envp))))
		return (0);
	if (!(new_env = export(exp_argv, g_envp, fd)))
		return (0);
	return (new_env);
}

static void	cd_error(char *target)
{
	ft_putstr_fd("ebash: cd: ", 2);
	ft_putstr_fd(target, 2);
	ft_putstr_fd(": ", 2);
	ft_putendl_fd(strerror(errno), 2);
}

int			cd(char **argv, int fd)
{
	char	**new_env;
	char	**exp_argv;
	char	*target;

	if (!argv[1])
		target = ft_getenv("HOME", g_envp);
	else
		target = argv[1];
	if (!(new_env = update_oldpwd(fd)))
		return (1);
	g_envp = new_env;
	if (chdir(target) < 0)
	{
		cd_error(target);
		return (1);
	}
	if (!(exp_argv = ft_split("export PWD=", ' ')))
		return (1);
	free(exp_argv[1]);
	if (!(new_env = update_env(exp_argv, fd)))
		return (1);
	g_envp = new_env;
	return (0);
}
