/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_util.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmeizo <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/25 12:55:55 by tmeizo            #+#    #+#             */
/*   Updated: 2021/03/12 14:46:37 by bmicheal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	clear_cmd(t_command **cmd)
{
	t_command	*tmp;
	t_command	*next;

	tmp = *cmd;
	while (tmp)
	{
		next = tmp->next;
		free(tmp->path);
		free_split(tmp->argv);
		clear_rd(&tmp->redirect);
		free(tmp);
		tmp = next;
	}
	*cmd = 0;
}

int		is_builtin(t_command *cmd)
{
	g_sh.l_a = make_lower_string(cmd);
	return (ft_strcmp(g_sh.l_a, "echo") == 0 ||
			ft_strcmp(g_sh.l_a, "cd") == 0 ||
			ft_strcmp(g_sh.l_a, "pwd") == 0 ||
			ft_strcmp(g_sh.l_a, "export") == 0 ||
			ft_strcmp(g_sh.l_a, "unset") == 0 ||
			ft_strcmp(g_sh.l_a, "env") == 0 ||
			ft_strcmp(g_sh.l_a, "exit") == 0);
}
