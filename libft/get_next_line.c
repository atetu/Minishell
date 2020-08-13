/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atetu <atetu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/15 09:50:56 by thgermai          #+#    #+#             */
/*   Updated: 2020/07/08 12:20:02 by atetu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char			*ft_strjoin_gnl(char *s1, char *s2)
{
	size_t	s1len;
	size_t	s2len;
	char	*str;

	if (!s1 || !s2)
		return (NULL);
	s1len = ft_strlen(s1);
	s2len = ft_strlen(s2);
	if (!(str = (char *)ft_calloc(sizeof(char), (s1len + s2len + 1))))
		return (NULL);
	ft_strlcpy(str, s1, s1len + 1);
	ft_strlcpy(str + s1len, s2, s2len + 1);
	str[s1len + s2len] = '\0';
	if (s1)
		free(s1);
	return (str);
}

char			*ft_refresh_stock(char *stock, int i)
{
	char			*temp;

	if (stock[i])
	{
		temp = ft_strdup(stock + i + 1);
		free(stock);
		stock = temp;
	}
	else
	{
		free(stock);
		stock = NULL;
	}
	return (stock);
}

int				ft_exit_ret(int ret, char **buffer, char **stock)
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

static void		loop(int *go_on, int ret, char **buffer, char **stock)
{
	*go_on = 0;
	(*buffer)[ret] = '\0';
	*stock = ft_strjoin_gnl(*stock, *buffer);
	if ((ret - 1) < 0)
	{
		*go_on = 1;
		write(1, "  \b\b", 4);
	}
	else if ((*buffer)[ret - 1] != '\n')
	{
		*go_on = 1;
		write(1, "  \b\b", 4);
	}
}

int				get_next_line(int fd, char **line, int *go_on)
{
	static char		*stock[1024];
	char			*buffer;
	int				ret;
	int				i;

	if (BUFFER_SIZE <= 0 || !line || fd < 0 || fd > 1024 ||
		!(buffer = (char *)ft_calloc(sizeof(char), (BUFFER_SIZE + 1))))
		return (ft_exit_ret(-1, &buffer, &stock[fd]));
	if (!stock[fd])
		stock[fd] = (char *)ft_calloc(sizeof(char), 1);
	while (!ft_strchr(buffer, '\n') && ((ret = read(fd, buffer, BUFFER_SIZE))
	|| (!ret && *go_on)))
	{
		if (ret == -1)
			return (ft_exit_ret(-1, &buffer, &stock[fd]));
		loop(go_on, ret, &buffer, &stock[fd]);
	}
	i = 0;
	while (stock[fd][i] && stock[fd][i] != '\n')
		i++;
	*line = ft_substr(stock[fd], 0, i);
	stock[fd] = ft_refresh_stock(stock[fd], i);
	if (ret || stock[fd])
		return (ft_exit_ret(1, &buffer, &stock[fd]));
	return (ft_exit_ret(0, &buffer, &stock[fd]));
}
