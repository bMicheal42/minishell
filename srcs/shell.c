/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmicheal <bmicheal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/03 10:43:21 by bmicheal          #+#    #+#             */
/*   Updated: 2021/03/12 14:46:35 by bmicheal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

pid_t		g_pid;
char		**g_envp;
int			g_exit_status;
t_shell		g_sh;

void	ft_main_loop_free(void)
{
	clear_tokens(&g_sh.head);
	clear_cmd(&g_sh.cmd);
	free(g_sh.input);
	free(g_sh.l_a);
}

void	ft_init(void)
{
	ft_putstr_fd("\033[0;32m\033[1mebash$ \033[0m", 2);
	signal(SIGINT, ft_sig_int);
	signal(SIGQUIT, ft_sig_quit);
	g_sh.j = 0;
	g_sh.i = 0;
	g_sh.cmd = 0;
	g_sh.input = NULL;
	if (!(g_sh.token = malloc(sizeof(t_token))))
		ft_error_list(3);
	g_sh.head = g_sh.token;
	g_sh.token->data = ft_calloc(4096, 1);
	g_sh.token->next = 0;
	g_sh.token->type = TOK_TEXT;
}

void	ft_read_input(void)
{
	while (g_sh.input[g_sh.i])
	{
		if (g_sh.input[g_sh.i] == '\\' && (ft_strchr(">|<; \'\"\\",
		g_sh.input[g_sh.i + 1])))
			ft_defined_data();
		else if (ft_strchr(">|<;", g_sh.input[g_sh.i]))
		{
			if ((ft_strchr(">|<;", g_sh.input[g_sh.i])) &&
			(!ft_check_quotes(g_sh.input, g_sh.i)))
				ft_next_token();
			else
				ft_defined_data();
		}
		else if ((g_sh.input[g_sh.i] == ' ' || g_sh.input[g_sh.i] == '\t') &&
				!ft_check_quotes(g_sh.input, g_sh.i))
		{
			ft_full_skip_token();
			continue ;
		}
		else
			g_sh.token->data[g_sh.j++] = g_sh.input[g_sh.i];
		g_sh.i++;
	}
}

void	ft_loop(int gnl_ret)
{
	while (gnl_ret)
	{
		ft_init();
		if (!(gnl_ret = get_next_line(0, &g_sh.input)))
		{
			if (*g_sh.input)
				gnl_ret = 1;
			free(g_sh.input);
			continue ;
		}
		if (ft_check_quotes(g_sh.input, ALL))
		{
			quotes_error();
			continue;
		}
		ft_read_input();
		sanitize_tokens(&g_sh.head);
		if (g_sh.head && check_syntax(g_sh.head) == 0)
		{
			g_sh.cmd = parse_cmd(g_sh.head, g_envp);
			if (g_sh.cmd)
				g_exit_status = execute(g_sh.cmd);
		}
		ft_main_loop_free();
	}
}

int		main(int argc, char **argv, char **env)
{
	char	**exp_argv;

	(void)argc;
	(void)argv;
	g_envp = copy_split(env);
	exp_argv = ft_split("export OLDPWD=", ' ');
	g_envp = export(exp_argv, g_envp, 0);
	free_split(exp_argv);
	g_exit_status = 0;
	print_greeting();
	ft_loop(1);
	free_split(g_envp);
	return (g_exit_status);
}
