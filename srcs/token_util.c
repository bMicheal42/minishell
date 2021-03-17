/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_util.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmicheal <bmicheal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/03 10:48:36 by bmicheal          #+#    #+#             */
/*   Updated: 2021/03/12 14:46:35 by bmicheal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_write(char *s, int i)
{
	write(2, &s[i], 1);
	write(2, &s[i + 1], 1);
}

void	syntax_error(char t_t, char *s, int i)
{
	t_t = (t_t == 'R') ? '>' : t_t;
	while (s[i] != t_t)
		i++;
	if (t_t == '>' || t_t == '<')
	{
		if (s[i + 1] == ';' || (s[i + 1] == t_t && s[i + 2] == ';'))
			write(2, ";", 1);
		else if (s[i + 1] != t_t || (s[i + 1] == t_t && s[i + 2] != t_t))
			ft_putstr_fd("newline", 2);
		else if (s[i + 1] == t_t && s[i + 2] == t_t && s[i + 3] != t_t)
			write(2, &s[i], 1);
		else if (s[i + 1] == t_t && s[i + 2] == t_t && s[i + 3] == t_t)
			ft_write(s, i);
	}
	else
	{
		if (s[i] == t_t && s[i + 1] == t_t)
			ft_write(s, i);
		else
			write(2, &s[i], 1);
	}
}

void	sanitize_tokens(t_token **token)
{
	t_token	*cur;
	t_token	*prev;

	while (*token && !*(*token)->data && (*token)->type == TOK_TEXT)
	{
		cur = (*token)->next;
		free((*token)->data);
		free(*token);
		*token = cur;
	}
	if (!(prev = *token))
		return ;
	cur = prev->next;
	while (cur)
	{
		if (cur && !*cur->data && cur->type == TOK_TEXT)
		{
			prev->next = cur->next;
			free(cur->data);
			free(cur);
			cur = prev;
		}
		prev = cur;
		cur = cur->next;
	}
}

int		check_syntax(t_token *token)
{
	if (token->type == TOK_SEMI || token->type == TOK_PIPE)
	{
		ft_putstr_fd("ebash: syntax error near unexpected token `", 2);
		syntax_error(token->type, g_sh.input, 0);
		ft_putendl_fd("'", 2);
		g_exit_status = 258;
		return (258);
	}
	while (token)
	{
		if (((token->type == TOK_REDA || token->type == TOK_REDO ||
			token->type == TOK_REDI || token->type == TOK_PIPE) &&
			(!token->next || token->next->type != TOK_TEXT)) ||
			(token->type == TOK_SEMI && token->next && (token->next->type
			== TOK_SEMI || token->next->type == TOK_PIPE)))
		{
			ft_putstr_fd("ebash: syntax error near unexpected token `", 2);
			syntax_error(token->type, g_sh.input, 0);
			ft_putendl_fd("'", 2);
			g_exit_status = 258;
			return (258);
		}
		token = token->next;
	}
	return (0);
}

void	clear_tokens(t_token **token)
{
	t_token	*tmp;
	t_token	*next;

	tmp = *token;
	while (tmp)
	{
		next = tmp->next;
		free(tmp->data);
		free(tmp);
		tmp = next;
	}
	*token = 0;
}
