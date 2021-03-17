/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmeizo <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/22 14:03:52 by tmeizo            #+#    #+#             */
/*   Updated: 2021/03/12 14:46:35 by bmicheal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char			*my_join(char *a, char *b)
{
	char	*ret;

	if (!a || !b)
		return (0);
	ret = ft_strjoin(a, b);
	free(a);
	free(b);
	return (ret);
}

static char		*expand_var(char *s, char **envp, int *i)
{
	char	*ret;
	char	*name;
	int		j;

	j = 0;
	if (s[0] && s[0] == '?')
	{
		(*i)++;
		return (ft_itoa(g_exit_status));
	}
	if (s[0] && !ft_isalpha(s[0]) && s[0] != '_')
	{
		(*i) = s[0] == '"' ? *i : *i + 1;
		return (ft_strdup(""));
	}
	while (s[j] && (ft_isalnum(s[j]) || s[j] == '_'))
		j++;
	name = ft_substr(s, 0, j);
	*i += j;
	ret = ft_strdup(ft_getenv(name, envp));
	free(name);
	return (ret);
}

static int		parse_quotes(char *s, t_tok_parser *p)
{
	if (s[p->i] == '"' && p->qt != QUOTE)
	{
		p->ret = my_join(p->ret, ft_substr(s, p->j, p->i - p->j));
		p->j = p->i + 1;
		p->qt = p->qt == DQUOTE ? 0 : DQUOTE;
		return (1);
	}
	if (s[p->i] == '\'' && p->qt != DQUOTE)
	{
		p->ret = my_join(p->ret, ft_substr(s, p->j, p->i - p->j));
		p->j = p->i + 1;
		p->qt = p->qt == QUOTE ? 0 : QUOTE;
		return (1);
	}
	return (0);
}

t_tok_parser	ft_init_token_parser(void)
{
	t_tok_parser	p;

	p.ret = ft_strdup("");
	p.i = 0;
	p.j = 0;
	p.qt = 0;
	return (p);
}

char			*parse_token(char *s, char **envp)
{
	t_tok_parser	p;

	p = ft_init_token_parser();
	while (s[p.i])
	{
		if (!p.ret)
			return (0);
		if (parse_quotes(s, &p))
			;
		else if (s[p.i] == '~' && !p.qt)
			token_util_tild(&p, envp, s);
		else if (s[p.i] == '\\' && p.qt != QUOTE)
			token_util_other(&p, s);
		else if ((s[p.i] == '$' && s[p.i + 1] && s[p.i + 1] != '\\' &&
			s[p.i + 1] != '%' && s[p.i + 1] != '/' && s[p.i + 1] != '=' &&
			!(p.qt == DQUOTE && s[p.i + 1] == '"')) && p.qt != QUOTE)
		{
			p.ret = my_join(p.ret, ft_substr(s, p.j, p.i++ - p.j));
			p.ret = my_join(p.ret, expand_var(s + p.i, envp, &p.i));
			p.j = p.i--;
		}
		p.i++;
	}
	p.ret = my_join(p.ret, ft_substr(s, p.j, p.i - p.j));
	return (p.ret);
}
