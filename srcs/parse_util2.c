/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_util2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmicheal <bmicheal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/04 14:06:23 by bmicheal          #+#    #+#             */
/*   Updated: 2021/03/12 14:46:35 by bmicheal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	token_util_other(t_tok_parser *p, char *s)
{
	if (!p->qt || (p->qt == DQUOTE && (s[p->i + 1] == '"' || s[p->i + 1] ==
	'$' || s[p->i + 1] == '\\' || s[p->i + 1] == '`')))
	{
		p->ret = my_join(p->ret, ft_substr(s, p->j, p->i - p->j));
		p->j = ++p->i;
	}
}

void	token_util_tild(t_tok_parser *p, char **envp, char *s)
{
	p->ret = my_join(p->ret, ft_substr(s, p->j, p->i - p->j));
	p->ret = my_join(p->ret, ft_strdup(ft_getenv("HOME", envp)));
	p->j = p->i + 1;
}
