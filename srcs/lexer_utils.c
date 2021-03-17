/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmicheal <bmicheal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/03 11:07:31 by bmicheal          #+#    #+#             */
/*   Updated: 2021/03/12 14:46:37 by bmicheal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void		ft_defined_data(void)
{
	if (g_sh.input[g_sh.i + 1] == '>' && g_sh.input[g_sh.i + 2] == '>')
	{
		g_sh.token->data[g_sh.j++] = g_sh.input[g_sh.i++];
		g_sh.token->data[g_sh.j++] = g_sh.input[g_sh.i++];
		g_sh.token->data[g_sh.j++] = g_sh.input[g_sh.i];
	}
	else if (ft_strchr(">|<; \'\"\\", g_sh.input[g_sh.i + 1]))
		g_sh.token->data[g_sh.j++] = g_sh.input[g_sh.i++];
	g_sh.token->data[g_sh.j++] = g_sh.input[g_sh.i];
}

void		ft_skip_token(void)
{
	g_sh.j = 0;
	if (!(g_sh.token->next = malloc(sizeof(t_token))))
		ft_error_list(3);
	g_sh.token = g_sh.token->next;
	g_sh.token->data = ft_calloc(4096, 1);
	g_sh.token->next = 0;
	g_sh.token->type = TOK_TEXT;
}

void		ft_full_skip_token(void)
{
	while (g_sh.input[g_sh.i] == ' ' || g_sh.input[g_sh.i] == '\t')
		g_sh.i++;
	ft_skip_token();
}

void		ft_next_token(void)
{
	ft_skip_token();
	if (g_sh.input[g_sh.i] == '>' && g_sh.input[g_sh.i + 1] == '>')
	{
		g_sh.token->type = TOK_REDA;
		g_sh.i++;
	}
	else if (g_sh.input[g_sh.i] == '<')
		g_sh.token->type = TOK_REDI;
	else if (g_sh.input[g_sh.i] == '>')
		g_sh.token->type = TOK_REDO;
	else if (g_sh.input[g_sh.i] == ';')
		g_sh.token->type = TOK_SEMI;
	else if (g_sh.input[g_sh.i] == '|')
		g_sh.token->type = TOK_PIPE;
	ft_skip_token();
}

int			ft_check_quotes(char *str, int num)
{
	int	i;
	int	open;

	i = 0;
	open = 0;
	while (str[i] && i < num)
	{
		if (str[i] == '\\' && ((open == 1 && (str[i + 1] == '"' ||
			str[i + 1] == '$' || str[i + 1] == '\\')) || !open))
			i++;
		else if (open == 0 && str[i] == '\"')
			open = 1;
		else if (open == 0 && str[i] == '\'')
			open = 2;
		else if (open == 1 && str[i] == '\"')
			open = 0;
		else if (open == 2 && str[i] == '\'')
			open = 0;
		i++;
	}
	return (open);
}
