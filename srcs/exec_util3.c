/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_util3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmicheal <bmicheal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/04 14:28:27 by bmicheal          #+#    #+#             */
/*   Updated: 2021/03/12 14:46:35 by bmicheal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int		ft_exec_util1(t_command *cmd)
{
	ft_putstr_fd("ebash: fork: ", 2);
	ft_putendl_fd(strerror(errno), 2);
	if (cmd->pipe_type & PIPE_IN)
		exit(128);
	return (128);
}

void	ft_exec_util2(void)
{
	wait(&g_exit_status);
	exit(g_exit_status >> 8);
}

int		ft_exec_util3(t_command *cmd, int status)
{
	if (cmd->argv[0] && is_builtin(cmd))
		g_exit_status = exec_builtin(cmd);
	else if (cmd->argv[0])
		ft_exec_argv(cmd, status);
	exec_cleanup(cmd);
	if (cmd->pipe_type & PIPE_IN && cmd->pipe_type & PIPE_OUT)
		ft_exec_util2();
	else if (cmd->pipe_type & PIPE_OUT)
	{
		wait(&g_exit_status);
		g_exit_status >>= 8;
		return (1);
	}
	else if (cmd->pipe_type & PIPE_IN && !cmd->next)
		exit(g_exit_status);
	return (0);
}

void	ft_exec_util4(t_command *cmd)
{
	process_pipe(cmd);
	g_pid = fork();
}

void	ft_exec_util5(t_command *cmd)
{
	if (!(cmd->pipe_type & PIPE_IN))
		close(cmd->pipe[0]);
}
