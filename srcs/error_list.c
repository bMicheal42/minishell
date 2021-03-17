/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmicheal <bmicheal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/03 11:25:12 by bmicheal          #+#    #+#             */
/*   Updated: 2021/03/12 14:46:35 by bmicheal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	quotes_error(void)
{
	ft_putstr_fd("Error:\nClose the qoutes\n", 2);
	g_exit_status = 2;
	free(g_sh.input);
	g_sh.input = NULL;
	clear_cmd(&g_sh.cmd);
	clear_tokens(&g_sh.head);
}

void	ft_error_list(int error)
{
	if (error == 1)
		ft_putstr_fd("Error:\nNo argument\n", 2);
	else if (error == 3)
		ft_putstr_fd("Error:\nMemory allocation failed\n", 2);
	else if (error == 4)
		ft_putstr_fd("Error:\nFork failed\n", 2);
	free(g_sh.input);
	g_sh.input = NULL;
	clear_cmd(&g_sh.cmd);
	clear_tokens(&g_sh.head);
	exit(1);
}
