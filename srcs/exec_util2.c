/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_util2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmeizo <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/27 10:48:39 by tmeizo            #+#    #+#             */
/*   Updated: 2021/03/12 14:46:35 by bmicheal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	rd_error(char *file)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(file, 2);
	ft_putstr_fd(": ", 2);
	ft_putendl_fd(strerror(errno), 2);
	return (1);
}

int			process_rd(t_command *cmd)
{
	t_redirect	*tmp;

	tmp = cmd->redirect;
	while (tmp)
	{
		if (tmp->type == RD_IN)
		{
			if (cmd->fd_in >= 0)
				close(cmd->fd_in);
			if ((cmd->fd_in = open(tmp->file, O_RDONLY)) < 0)
				return (rd_error(tmp->file));
		}
		else
		{
			if (cmd->fd_out >= 0)
				close(cmd->fd_out);
			if ((cmd->fd_out = open(tmp->file, O_CREAT | O_WRONLY |
					(tmp->type == RD_OUTA ? O_APPEND : O_TRUNC), 0644)) < 0)
				return (rd_error(tmp->file));
		}
		tmp = tmp->next;
	}
	return (0);
}

int			process_pipe(t_command *cmd)
{
	int	pp[2];

	if (cmd->pipe_type & PIPE_OUT)
	{
		if (cmd->pipe_type & PIPE_IN)
		{
			if (pipe(pp) == -1)
				return (1);
			cmd->pipe[1] = pp[1];
			cmd->next->pipe[0] = pp[0];
		}
		else
		{
			if (pipe(cmd->pipe) == -1)
				return (1);
			cmd->next->pipe[0] = cmd->pipe[0];
		}
	}
	return (0);
}

int			prepare_cmd(t_command *cmd)
{
	cmd->envp = g_envp;
	if (!(cmd->argv = parse_argv(cmd->token, cmd->envp)))
		return (1);
	if (process_rd(cmd) != 0)
	{
		g_exit_status = 1;
		return (1);
	}
	return (0);
}
