/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmeizo <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/21 16:15:25 by tmeizo            #+#    #+#             */
/*   Updated: 2021/03/12 14:46:35 by bmicheal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int			ft_notvalid_cmd(t_command *cmd)
{
	g_exit_status = 127;
	ft_putstr_fd("ebash: ", 2);
	ft_putstr_fd(cmd->argv[0], 2);
	ft_putstr_fd(": command not found\n", 2);
	return (g_exit_status);
}

void		exec_cleanup(t_command *cmd)
{
	if (cmd->fd_out >= 0)
		close(cmd->fd_out);
	if (cmd->fd_in >= 0)
		close(cmd->fd_in);
	if (cmd->pipe_type & PIPE_OUT)
		close(cmd->pipe[1]);
	if (cmd->pipe_type & PIPE_IN)
		close(cmd->pipe[0]);
}

static void	exec_child(t_command *cmd)
{
	free(cmd->argv[0]);
	cmd->argv[0] = ft_strdup(cmd->path);
	if (cmd->pipe_type & PIPE_OUT)
		dup2(cmd->pipe[1], 1);
	if (cmd->pipe_type & PIPE_IN)
		dup2(cmd->pipe[0], 0);
	if (cmd->fd_out >= 0)
		dup2(cmd->fd_out, 1);
	if (cmd->fd_in >= 0)
		dup2(cmd->fd_in, 0);
	if (execve(cmd->path, cmd->argv, cmd->envp) == -1)
	{
		ft_putstr_fd("ebash: ", 2);
		ft_putstr_fd(cmd->argv[0], 2);
		ft_putstr_fd(": ", 2);
		ft_putendl_fd(strerror(errno), 2);
		exit(127);
	}
	exec_cleanup(cmd);
	exit(0);
}

int			forked(t_command *cmd, int status)
{
	g_pid = fork();
	if (g_pid == 0)
		exec_child(cmd);
	else if (g_pid < 0)
		ft_error_list(4);
	else
	{
		waitpid(g_pid, &status, 0);
		g_pid = 0;
		if (g_exit_status != 130 && g_exit_status != 131)
			g_exit_status = status >> 8;
	}
	return (g_exit_status);
}

int			execute(t_command *cmd)
{
	int	status;

	while (cmd)
	{
		if ((status = prepare_cmd(cmd)) != 0)
			break ;
		if (cmd->pipe_type & PIPE_OUT)
		{
			ft_exec_util4(cmd);
			if (g_pid > 0)
				ft_exec_util5(cmd);
			else if (g_pid == 0)
			{
				close(cmd->pipe[1]);
				cmd = cmd->next;
				continue ;
			}
			else
				return (ft_exec_util1(cmd));
		}
		if (ft_exec_util3(cmd, status))
			break ;
		cmd = cmd->next;
	}
	return (g_exit_status);
}
