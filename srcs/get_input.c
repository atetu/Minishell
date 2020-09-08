/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_input.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thgermai <thgermai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/31 13:53:07 by thgermai          #+#    #+#             */
/*   Updated: 2020/08/31 15:48:26 by thgermai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int		ft_exit_ret(int ret, char **buffer, char **stock)
{
	if (ret >= 0 && (*buffer || *stock))
	{
		if (*buffer)
			free(*buffer);
		if (ret == 0 && *stock)
			free(*stock);
	}
	if (ret == -1)
	{
		if (!*buffer)
			free(*buffer);
		if (*stock)
			free(*stock);
	}
	return (ret);
}

static char		*refresh_stock(char *str, int i)
{
	char		*new_stock;

	if (str[i])
		new_stock = ft_strdup(str + i + 1);
	else
		new_stock = NULL;
	free(str);
	return (new_stock);
}

static int		loop(int *go_on, int ret, char **buffer, char **stock)
{
	if (*go_on != 2)
		*go_on = 0;
	(*buffer)[ret] = '\0';
	*stock = ft_strjoin_f1(*stock, *buffer);
	if (*go_on != 2 && (*buffer)[ret - 1] != '\n')
	{
		*go_on = 1;
		write(1, "  \b\b", 4);
	}
	return (1);
}

int				get_input(char **line, int *go, int opt)
{
	static char		*stock;
	char			*buffer;
	int				ret;
	int				i;

	if (BUFFER_SIZE <= 0 || !line || (ret = 0) ||
		!(buffer = (char *)ft_calloc(sizeof(char), (BUFFER_SIZE + 1))))
		return (ft_exit_ret(-1, &buffer, &stock));
	if (!stock && !(stock = ft_calloc(sizeof(char), 1)))
		return (ft_exit_ret(-1, &buffer, &stock));
	while (!ft_strchr(buffer, '\n') &&
		((ret = read(0, buffer, BUFFER_SIZE)) || (ret == 0 && *go && opt == 1)))
	{
		if (ret == -1)
			return (ft_exit_ret(-1, &buffer, &stock));
		loop(go, ret, &buffer, &stock);
	}
	i = 0;
	while (stock[i] && stock[i] != '\n')
		i++;
	*line = ft_substr(stock, 0, i);
	stock = refresh_stock(stock, i);
	if (ret || stock)
		return (ft_exit_ret(1, &buffer, &stock));
	return (ft_exit_ret(0, &buffer, &stock));
}

int				check_function(char **func, t_call *call)
{
	pid_t		pid;

	if (!known_func(func[0]))
	{
		if (!(func[0] = parse_exec(call, func[0])))
		{
			clean_array(func);
			if ((pid = fork()) == 0)
				exit(1);
			return (pid);
		}
	}
	return (-1);
}
