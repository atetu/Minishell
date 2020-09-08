/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_pipes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/18 21:49:31 by thgermai          #+#    #+#             */
/*   Updated: 2020/09/07 11:06:32 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int		return_get_n_pipes(char **temp, int i)
{
	free(*temp);
	return (i);
}

int				get_n_pipes(char *args, int option)
{
	int			i;
	int			n_pipes;
	char		*temp;

	parse_backslash((temp = ft_strdup(args)));
	i = -1;
	n_pipes = 0;
	while (temp[++i])
	{
		if (temp[i] == '|' && !is_valide(temp, i, 1) && (i == 0 ||
			(i > 0 && temp[i - 1] != -1)))
		{
			if (option == 1)
				return (return_get_n_pipes(&temp, i));
			n_pipes++;
		}
	}
	if (option == 1)
		return (return_get_n_pipes(&temp, -1));
	free(temp);
	return (n_pipes);
}

static int		check_pipes_args(t_call *calls)
{
	int			i;

	i = -1;
	while (calls[++i].str)
	{
		if (!ft_strlen(calls[i].str) || !arg_is_valid(calls[i].str))
		{
			ft_printf_e("minishell: syntax error near unexpected token `|'\n");
			exit_status_nb();
			return (-1);
		}
	}
	return (0);
}

int				parse_pipes(char *str, t_call *calls)
{
	int			i;
	int			last_i;

	last_i = 0;
	i = 0;
	while (get_n_pipes(str + last_i, 1) != -1)
	{
		calls[i].str = ft_substr(str + last_i, 0,
			get_n_pipes(str + last_i, 1));
		last_i += ft_strlen(calls[i].str) + 1;
		i++;
	}
	calls[i].str = ft_substr(str + last_i, 0, ft_strlen(str + last_i));
	calls[i + 1].str = NULL;
	if (check_pipes_args(calls) == -1)
		return (-1);
	return (0);
}
