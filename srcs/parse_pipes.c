/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_pipes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atetu <atetu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/18 21:49:31 by thgermai          #+#    #+#             */
/*   Updated: 2020/08/04 14:35:09 by atetu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int				get_n_pipes(char *args, int option)
{
	int			i;
	int			n_pipes;

	i = 0;
	n_pipes = 0;
	while (args[++i])
	{
		if (args[i] == '|' && !is_valide(args, i, 1) && (i == 0 ||
		(i > 0 && !is_backslash(args, i - 1)))) //ICI
		{
			if (option == 1)
				return (i);
			n_pipes++;
		}
	}
	if (option == 1)
		return (-1);
	return (n_pipes);
}

void			parse_pipes(char *str, t_call *calls)
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
}
