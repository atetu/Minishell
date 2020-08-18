/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thgermai <thgermai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/30 16:10:54 by atetu             #+#    #+#             */
/*   Updated: 2020/08/17 14:49:18 by thgermai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void			control_c(int sig)
{
	int i;

	(void)sig;
	if (!g_pids)
	{
		write(1, "\b\b  \b\b\n", 7);
		g_exit_status = 1;
		print();
	}
	else
	{
		i = -1;
		while (++i)
			kill(g_pids[i], sig);
		write(1, "\n", 1);
		g_exit_status = 130;
	}
}

int				control_d(void)
{
	g_exit_nb = g_exit_status;
	//	ft_printf("exit\n");  // selon moi a indiquer mais erreur avec le testeur
	return (1);
}

void			control_quit(int sig)
{
	int i;

	i = -1;
	if (g_pids) // variable globale a modifier quand fd = 0
	{
		ft_printf("Quit: %d\n", sig);
		while (++i)
			kill(g_pids[i], 2);
		g_exit_status = 131;
		g_exit_nb = g_exit_status;
	}
	else
	{
		write(1, "\b\b  \b\b", 6);
		g_exit_status = 0;
		g_exit_nb = 127;
	}
}
