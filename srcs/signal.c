/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmicheal <bmicheal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/03 10:43:42 by bmicheal          #+#    #+#             */
/*   Updated: 2021/03/12 14:46:35 by bmicheal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_sig_int(int a)
{
	if (a)
		a = 0;
	if (g_pid)
	{
		write(1, "\n", 1);
		g_exit_status = 130;
		g_pid = 0;
	}
	else
	{
		ft_putstr_fd("\n\033[0;32m\033[1mebash$ \033[0m", 2);
		g_exit_status = 1;
	}
}

void	ft_sig_quit(int a)
{
	if (g_pid)
	{
		ft_putstr_fd("Quit: ", 2);
		ft_putnbr_fd(a, 2);
		write(2, "\n", 1);
		g_pid = 0;
		g_exit_status = 131;
	}
	else
		ft_putstr_fd("\b\b  \b\b", 1);
}
