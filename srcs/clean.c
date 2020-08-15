/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atetu <atetu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/02 22:25:17 by thgermai          #+#    #+#             */
/*   Updated: 2020/08/11 16:24:24 by atetu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void			clean_calls(t_call *calls)
{
	int			i;

	i = -1;
	while (calls[++i].str)
		free(calls[i].str);
}

void			close_pipes(int pipes[][2], int size)
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
	if (array)  // ICI
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
	ft_lstclear(list, &free);
	free(g_pwd);
	free(g_oldpwd);
}