/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_util.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmeizo <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/25 10:57:48 by tmeizo            #+#    #+#             */
/*   Updated: 2021/03/12 14:46:35 by bmicheal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void		ft_exec_argv(t_command *cmd, int status)
{
	if (ft_strchr(cmd->argv[0], '/'))
		cmd->path = ft_strdup(cmd->argv[0]);
	else
		cmd->path = find_in_path(cmd->argv[0], cmd->envp);
	if (!cmd->path && g_pid == 0)
		g_exit_status = ft_notvalid_cmd(cmd);
	else
		g_exit_status = forked(cmd, status);
}

char		**ft_sort_by_name(char **s, int lim)
{
	int		i;
	int		j;
	char	*tmp;

	i = 0;
	while (i < lim)
	{
		j = i + 1;
		while (j < lim)
		{
			if (ft_strcmp(s[i], s[j]) > 0)
			{
				tmp = s[j];
				s[j] = s[i];
				s[i] = tmp;
			}
			j++;
		}
		i++;
	}
	return (s);
}

static int	find_in_dir(char *name, DIR *dir)
{
	struct dirent	*dnt;

	while ((dnt = readdir(dir)))
	{
		if (ft_strcmp(name, dnt->d_name) == 0)
		{
			closedir(dir);
			return (1);
		}
	}
	closedir(dir);
	return (0);
}

static char	*build_path(char *dirname, char *name)
{
	int		dlen;
	int		nlen;
	char	*ret;
	int		i;

	dlen = ft_strlen(dirname);
	nlen = ft_strlen(name);
	if (!(ret = malloc((dirname[dlen - 1] == '/' ? dlen : dlen + 1) +
		nlen + 1)))
		ft_error_list(3);
	if (dirname[dlen - 1] != '/')
		dirname[dlen++] = '/';
	i = 0;
	while (i < dlen)
	{
		ret[i] = dirname[i];
		i++;
	}
	while (i < dlen + nlen)
	{
		ret[i] = name[i - dlen];
		i++;
	}
	ret[i] = 0;
	return (ret);
}

char		*find_in_path(char *name, char **envp)
{
	DIR		*dir;
	char	*ret;
	char	**path;
	int		i;

	ret = 0;
	if (!(path = ft_split(ft_getenv("PATH", envp), ':')))
		return (0);
	if (!*path)
	{
		free_split(path);
		return (0);
	}
	i = 0;
	while (path[i] && !ret)
	{
		if (!(dir = opendir(path[i++])))
			continue ;
		if (find_in_dir(name, dir))
			ret = build_path(path[i - 1], name);
	}
	free_split(path);
	return (ret);
}
