/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmeizo <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/21 13:49:31 by tmeizo            #+#    #+#             */
/*   Updated: 2021/03/12 14:46:35 by bmicheal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	*build_env(char *old, char *new, int add, int repl)
{
	char	*ret;
	char	*name;
	char	*tmp;

	if (add)
	{
		if (repl)
		{
			name = ft_substr(old, 0, index_of(old, '=') + 1);
			tmp = ft_strjoin(name, ft_strchr(old, '=') + 1);
			ret = ft_strjoin(tmp, ft_strchr(new, '=') + 1);
			free(tmp);
		}
		else
		{
			name = ft_substr(new, 0, index_of(new, '+'));
			ret = ft_strjoin(name, ft_strchr(new, '='));
		}
		free(name);
	}
	else
		ret = ft_strdup(new);
	return (ret);
}

static char	**insert_env(char **envp, char *s, int name_len, int add)
{
	char	**ret;
	int		i;
	int		repl;

	repl = 0;
	i = env_len(envp, s, name_len, &repl);
	if (!(ret = malloc(sizeof(char *) * (i + 1))))
		ft_error_list(3);
	ret[i] = 0;
	if (!repl)
		ret[--i] = build_env(0, s, add, repl);
	while (i--)
	{
		if (repl && ft_strncmp(envp[i], s, name_len) == 0)
		{
			ret[i] = build_env(envp[i], s, add, repl);
			free(envp[i]);
		}
		else
			ret[i] = envp[i];
	}
	free(envp);
	return (ret);
}

static int	check_name(char *name)
{
	int	i;

	i = 0;
	if (ft_isdigit(name[0]) || name[0] == '=' || name[0] == '+')
		return (1);
	while (name[i] && name[i] != '=')
	{
		if (!ft_isalnum(name[i]) && name[i] != '_' && !(name[i] == '+'
		&& name[i + 1] == '='))
			return (1);
		i++;
	}
	return (0);
}

static void	print_exports(char **envp, int fd)
{
	int		i;
	int		k;
	char	**sorted_envp;

	i = 0;
	k = 0;
	sorted_envp = copy_split(envp);
	while (sorted_envp[i])
		i++;
	sorted_envp = ft_sort_by_name(sorted_envp, i);
	while (sorted_envp[k])
	{
		ft_putstr_fd("declare -x ", fd);
		i = 0;
		while (sorted_envp[k][i++] != '=')
			;
		write(fd, sorted_envp[k], sorted_envp[k][i] ? i : i - 1);
		if (sorted_envp[k][i])
			print_sorted_env(sorted_envp, fd, i, k);
		write(fd, "\n", 1);
		k++;
	}
	free_split(sorted_envp);
}

char		**export(char **argv, char **envp, int fd)
{
	char	*s;
	int		name_len;
	char	**ret;

	ret = envp;
	if (!*(++argv))
		print_exports(ret, fd);
	while (*argv)
	{
		s = *argv;
		name_len = index_of(s, '=');
		if ((g_exit_status = check_name(s)) == 0)
		{
			if (name_len >= 0)
			{
				ret = s[name_len - 1] == '+' ? insert_env(ret, s, name_len -
				1, 1) : insert_env(ret, s, name_len, 0);
			}
		}
		else
			export_error(s);
		argv++;
	}
	return (ret);
}
