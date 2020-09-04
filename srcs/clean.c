/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/02 22:25:17 by thgermai          #+#    #+#             */
/*   Updated: 2020/09/04 16:17:53 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void			clean_calls(t_call *calls)
{
	int			i;

	i = -1;
	while (calls[++i].str)
		free(calls[i].str);
	free(calls);
}

void			clean_pipes(int **pipes, int n_pipes)
{
	int			i;

	i = 0;
	if (n_pipes)
	{
		while (i < n_pipes)
		{
			free(pipes[i]);
			i++;
		}
	}
	if (pipes)
		free(pipes);
}

void			close_pipes(int **pipes, int size)
{
	int			i;

	i = -1;
	while (++i < size)
	{
		close(pipes[i][0]);
		close(pipes[i][1]);
	}
}

void			clean_array(char **array)
{
	int			i;

	i = -1;
	if (array)
	{
		while (array[++i])
			free(array[i]);
		free(array);
	}
}

void			clear_all(char *args, t_list **list)
{
	if (args)
		free(args);
	get_input(NULL, NULL, 0);
	ft_lstclear(list, &free);
	free(list);
	free(g_pwd);
	free(g_oldpwd);
	free(g_home);
	free(g_last);
}
