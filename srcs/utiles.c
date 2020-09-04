/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utiles.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/18 23:43:21 by thgermai          #+#    #+#             */
/*   Updated: 2020/09/04 13:51:25 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char			*get_cwd(void)
{
	char		buffer[1024];
	char		*cwd;

	ft_memset(&buffer, 0, 1024);
	cwd = getcwd(buffer, 1024);
	if (!cwd)
		ft_printf("%s\n", strerror(errno));
	return (cwd);
}

int				known_func(char *str)
{
	if (!ft_strncmp(str, "echo", 5))
		return (1);
	else if (!ft_strncmp(str, "cd", 3))
		return (1);
	else if (!ft_strncmp(str, "pwd", 4))
		return (1);
	else if (!ft_strncmp(str, "export", 7))
		return (1);
	else if (!ft_strncmp(str, "unset", 6))
		return (1);
	else if (!ft_strncmp(str, "env", 4))
		return (1);
	else if (!ft_strncmp(str, "exit", 5))
		return (1);
	return (0);
}

int				is_backslash(char *str, int index)
{
	int			backslash;

	backslash = 0;
	while (index >= 0 && str[index] == '\\')
	{
		index--;
		backslash++;
	}
	if (backslash != 0 && backslash % 2 != 0)
		return (1);
	return (0);
}

int				arg_is_valid(char *str)
{
	int			i;

	i = -1;
	while (str[++i])
		if (str[i] != ' ')
			return (1);
	return (0);
}
