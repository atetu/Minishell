/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_pipes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atetu <atetu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/02 22:31:11 by thgermai          #+#    #+#             */
/*   Updated: 2020/08/24 16:50:46 by atetu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void			wait_pids(pid_t *pids, int size, t_call *calls)
{
	int			i;
	int			status;

	i = -1;
	(void)calls;
	while (++i < size && pids[i] != -1)
	{
		waitpid(pids[i], &status, 0);
		if (WIFEXITED(status))
		{
			g_exit_status = WEXITSTATUS(status);
			g_exit_nb = g_exit_status;
		}
	}
}

void			manage_pipes(t_call *calls, int pipes[][2],
	char *str, int *exit_info)
{
	int i;
	int n_pipes;

	n_pipes = create_pipes(calls, pipes);
	i = -1;
	while (calls[++i].str)
		connect_pipes(calls, pipes, n_pipes);
	i = -1;
	while (calls[++i].str)
		g_pids[i] = exec1(&calls[i], pipes, get_n_pipes(str, 0), exit_info);
	close_pipes(pipes, get_n_pipes(str, 0));
	wait_pids(g_pids, get_n_pipes(str, 0) + 1, calls);
}

int				create_pipes(t_call *calls, int pipes[][2])
{
	int			i;
	int			size;

	i = 0;
	while (calls[i].str)
		i++;
	size = --i;
	if (size == 0)
		return (0);
	i = -1;
	while (++i < size)
	{
		if (pipe(pipes[i]) == -1)
		{
			ft_printf_e("Error: pipe creation failed\n");
			exit(0);
		}
	}
	return (size);
}

void			connect_pipes(t_call *calls, int pipes[][2], int n_pipes)
{
	int			i;

	i = -1;
	while (calls[++i].str)
	{
		if (calls[i].in != 0)
			;
		else if (calls[i].in == 0 && i != 0)
			calls[i].in = pipes[i - 1][0];
		if (calls[i].out != 1)
			;
		else if (calls[i].out == 1 && i < n_pipes && pipes[i][0])
			calls[i].out = pipes[i][1];
	}
}
