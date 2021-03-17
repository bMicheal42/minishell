/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmeizo <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/22 13:53:05 by tmeizo            #+#    #+#             */
/*   Updated: 2021/03/12 14:46:37 by bmicheal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static t_command	*init_cmd(t_token *token)
{
	t_command	*ret;

	if (!(ret = malloc(sizeof(t_command))))
		ft_error_list(3);
	ret->token = token;
	ret->argv = 0;
	ret->path = 0;
	ret->envp = 0;
	ret->redirect = 0;
	ret->fd_in = -1;
	ret->fd_out = -1;
	ret->pipe_type = 0;
	ret->pipe[0] = -1;
	ret->pipe[1] = -1;
	ret->next = 0;
	return (ret);
}

static t_command	*parse_error(t_command *cmd)
{
	t_command	*tmp;

	tmp = cmd;
	while (tmp)
	{
		free_split(tmp->argv);
		clear_rd(&tmp->redirect);
		tmp = tmp->next;
	}
	return (0);
}

static t_command	*parse_pipe_semi(t_command *cmd, t_token *token)
{
	if (token->type == TOK_PIPE)
	{
		cmd->pipe_type |= POLL_OUT;
		cmd->next = init_cmd(token->next);
		cmd->next->pipe_type |= PIPE_IN;
	}
	else if (token->next)
		cmd->next = init_cmd(token->next);
	return (cmd->next);
}

t_command			*parse_cmd(t_token *token, char **envp)
{
	t_command	*ret;
	t_command	*tmp;

	if (!(ret = init_cmd(token)))
		return (0);
	tmp = ret;
	while (token)
	{
		if (token->type == TOK_REDI ||
			token->type == TOK_REDO || token->type == TOK_REDA)
		{
			if (!token->next || token->next->type != TOK_TEXT)
				return (parse_error(ret));
			append_rd(&tmp->redirect, token->type,
				parse_token(token->next->data, envp));
			token = token->next;
		}
		else if (token->type == TOK_PIPE || token->type == TOK_SEMI)
			tmp = parse_pipe_semi(tmp, token);
		token = token->next;
	}
	return (ret);
}
