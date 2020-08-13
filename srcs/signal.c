/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atetu <atetu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/30 16:10:54 by atetu             #+#    #+#             */
/*   Updated: 2020/07/08 16:14:07 by atetu            ###   ########.fr       */
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
		exit_status = 1;
		print();
	}
	else
	{
		i = -1;
		while(++i)
			kill(g_pids[i], sig);
		write(1, "\n", 1);
		exit_status = 130;
	}
}

int				control_d(void)
{
	int i;

	i = -1;
	if (!g_pids)
	{
    //	write(1, "\b   \b\b", 6);
    //    ft_printf("exit\n");
		exit_status = 0;
        return(0);
	}
	else
	{
		while(++i)
			kill(g_pids[i], 2);
//		ft_printf("exit\n");
		exit_status = 0;
		return (0);
	}
	return (1);
}

void			control_quit(int sig)
{
	int i;

	i = -1;
	if (g_pids) // variable globale a modifier quand fd = 0
	{
		ft_printf("Quit: %d\n", sig);
		while(++i)
			kill(g_pids[i], 2);
		exit_status = 131;
	}
	else
	{
		write(1, "\b\b  \b\b", 6);
		exit_status = 127;
	}
}
