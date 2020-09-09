/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_utiles.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/04 15:07:15 by user42            #+#    #+#             */
/*   Updated: 2020/09/09 11:01:17 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void			print(void)
{
	ft_printf_e("\033[1;32mMINISHELL \033[0m👉 ");
}

t_call			*init_array(char *str)
{
	t_call		*calls;

	if (!(calls = malloc(sizeof(t_call) * (get_n_pipes(str, 0) + 2))))
		return (NULL);
	if (!(g_pids = malloc(sizeof(pid_t) * (get_n_pipes(str, 0) + 2))))
	{
		ft_printf_e("minishell: error: malloc failed\n");
		return (NULL);
	}
	return (calls);
}

int				init_pipes(int n_pipes, int ***pipes)
{
	int i;

	i = 0;
	if (n_pipes)
	{
		if (!(*pipes = malloc(sizeof(int *) * n_pipes)))
			return (0);
		while (i < n_pipes)
		{
			(*pipes)[i] = NULL;
			if (!((*pipes)[i] = malloc(sizeof(int) * 2)))
				return (0);
			i++;
		}
	}
	return (1);
}
