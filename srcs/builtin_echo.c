/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/04 10:26:57 by user42            #+#    #+#             */
/*   Updated: 2020/09/04 10:27:21 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int		check_flag(char **func, int i)
{
	if (i == 1 && !ft_strncmp(func[1], "-n", 3))
		return (1);
	if (i > 1)
	{
		if (!ft_strncmp(func[i], "-n", 3))
		{
			while (i > 1)
			{
				if (ft_strncmp(func[i], "-n", 3))
					break ;
				i--;
			}
			if (i == 1)
				return (1);
			return (0);
		}
	}
	return (0);
}

int				ft_echo(char **func)
{
	int			i;
	int			space;

	i = 0;
	space = 1;
	if (func[1] && ft_strncmp(func[1], "-n", 3) == 0)
		space = 0;
	while (func[++i])
	{
		if (check_flag(func, i))
			;
		else
		{
			if (write(1, func[i], ft_strlen(func[i])) == -1)
			{
				ft_printf_e("%s\n", strerror(errno));
				return (EXIT_FAILURE);
			}
			if (func[i + 1])
				write(1, " ", 1);
		}
	}
	if (space)
		write(1, "\n", 1);
	return (EXIT_SUCCESS);
}
