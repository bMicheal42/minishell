/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmeizo <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/26 10:20:31 by tmeizo            #+#    #+#             */
/*   Updated: 2021/03/12 14:46:37 by bmicheal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char		*make_lower_string(t_command *cmd)
{
	int		i;
	char	*s;

	i = 0;
	s = ft_strdup(cmd->argv[0]);
	while (s[i])
	{
		s[i] = (char)ft_tolower(s[i]);
		i++;
	}
	return (s);
}

static int	check_fd(t_command *cmd)
{
	if (cmd->fd_out >= 0)
		return (cmd->fd_out);
	if (cmd->pipe_type & PIPE_OUT)
		return (cmd->pipe[1]);
	return (1);
}

static int	continue_exec(t_command *cmd, int fd)
{
	if (ft_strcmp(g_sh.l_a, "env") == 0)
		return (env(cmd->envp, fd));
	else if (ft_strcmp(g_sh.l_a, "exit") == 0 && !cmd->pipe_type)
	{
		ft_putendl_fd("exit", 2);
		ft_exit(cmd->argv);
	}
	return (g_exit_status);
}

int			exec_builtin(t_command *cmd)
{
	char	**new_env;
	int		fd;

	fd = check_fd(cmd);
	if (ft_strcmp(g_sh.l_a, "echo") == 0)
		return (echo(cmd->argv, fd));
	else if (ft_strcmp(g_sh.l_a, "cd") == 0)
		return (cd(cmd->argv, fd));
	else if (ft_strcmp(g_sh.l_a, "pwd") == 0)
		return (pwd(fd));
	else if (ft_strcmp(g_sh.l_a, "export") == 0)
	{
		if (!(new_env = export(cmd->argv, cmd->envp, fd)))
			return (1);
		g_envp = new_env;
	}
	else if (ft_strcmp(g_sh.l_a, "unset") == 0)
	{
		if (!(new_env = unset(cmd->argv, cmd->envp)))
			return (1);
		g_envp = new_env;
	}
	else
		return (continue_exec(cmd, fd));
	return (g_exit_status);
}
