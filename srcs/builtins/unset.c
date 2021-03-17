/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmeizo <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/21 15:16:45 by tmeizo            #+#    #+#             */
/*   Updated: 2021/03/12 14:46:37 by bmicheal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	valid_name(char *s)
{
	if (ft_isdigit(*s))
		return (1);
	while (*s)
		if ((!ft_isalnum(*s) && *s != '_') || *s++ == '=')
			return (1);
	return (0);
}

static int	calc_new_size(char **envp, char *s)
{
	int	ret;
	int	i;

	ret = 0;
	i = 0;
	while (envp[i])
	{
		if (cmp_name(envp[i], s))
			ret--;
		i++;
		ret++;
	}
	return (ret);
}

static char	**del_env(char **envp, char *s)
{
	int		i;
	int		j;
	char	**ret;

	i = 0;
	i = calc_new_size(envp, s);
	if (!(ret = malloc(sizeof(char *) * (i + 1))))
		ft_error_list(3);
	i = 0;
	j = 0;
	while (envp[j])
	{
		if (!cmp_name(envp[j], s))
			ret[i++] = envp[j];
		else
			free(envp[j]);
		j++;
	}
	ret[i] = 0;
	free(envp);
	return (ret);
}

char		**unset(char **argv, char **envp)
{
	char	*s;
	char	**ret;

	ret = envp;
	argv++;
	while (*argv)
	{
		s = *argv;
		if ((valid_name(s)) == 0)
			ret = del_env(ret, s);
		else
		{
			ft_putstr_fd("ebash: unset: '", 2);
			ft_putstr_fd(s, 2);
			ft_putendl_fd("': not a valid identifier", 2);
			g_exit_status = 1;
		}
		argv++;
	}
	return (ret);
}
