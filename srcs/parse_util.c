/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_util.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmicheal <bmicheal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/03 10:51:26 by bmicheal          #+#    #+#             */
/*   Updated: 2021/03/12 14:46:35 by bmicheal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void		append_rd(t_redirect **rd, char type, char *filename)
{
	t_redirect *tmp;

	if (!*rd)
	{
		if (!(*rd = malloc(sizeof(t_redirect))))
			ft_error_list(3);
		(*rd)->type = type;
		(*rd)->file = filename;
		(*rd)->next = 0;
		return ;
	}
	tmp = *rd;
	while (tmp->next)
		tmp = tmp->next;
	if (!(tmp->next = malloc(sizeof(t_redirect))))
		ft_error_list(3);
	tmp->next->type = type;
	tmp->next->file = filename;
	tmp->next->next = 0;
}

void		clear_rd(t_redirect **rd)
{
	t_redirect	*tmp;
	t_redirect	*prev;

	tmp = *rd;
	prev = tmp;
	while (tmp)
	{
		tmp = tmp->next;
		free(prev->file);
		free(prev);
		prev = tmp;
	}
	*rd = 0;
}

static int	count_argv(t_token *token)
{
	int	len;

	len = 0;
	while (token && token->type != TOK_PIPE && token->type != TOK_SEMI)
	{
		if (token->type == TOK_REDI || token->type == TOK_REDO ||
			token->type == TOK_REDA)
			token = token->next;
		else
			len++;
		token = token->next;
	}
	return (len);
}

static char	*check_empty_var(char *data, char *parsed)
{
	if (ft_strchr(data, '$') && !*parsed)
	{
		free(parsed);
		return (0);
	}
	return (parsed);
}

char		**parse_argv(t_token *token, char **envp)
{
	char	**ret;
	int		len;
	int		i;

	len = count_argv(token);
	if (!(ret = malloc(sizeof(char *) * (len + 1))))
		ft_error_list(3);
	i = 0;
	while (i < len && token &&
		token->type != TOK_SEMI && token->type != TOK_PIPE)
	{
		if (token->type == TOK_REDI || token->type == TOK_REDO ||
			token->type == TOK_REDA)
			token = token->next;
		else if (token->type == TOK_TEXT)
		{
			ret[i] = parse_token(token->data, envp);
			if ((ret[i] = check_empty_var(token->data, ret[i])))
				i++;
		}
		token = token->next;
	}
	ret[i] = 0;
	return (ret);
}
