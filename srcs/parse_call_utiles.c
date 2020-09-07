/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_call_utiles.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/24 15:55:52 by atetu             #+#    #+#             */
/*   Updated: 2020/09/07 16:02:20 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	handle_file_name_error(char *str)
{
	while (*str && *str != ' ')
		str++;
	while (*str && *str == ' ')
		str++;
	if (!ft_strncmp("<", str, 2))
		ft_printf_e("minishell: %s `<'\n", SYNTAX_ERR);
	else if (!ft_strncmp("<<", str, 3))
		ft_printf_e("minishell: %s `<<'\n", SYNTAX_ERR);
	else if (!ft_strncmp("<<<", str, 3))
		ft_printf_e("minishell: %s `<<<'\n", SYNTAX_ERR);
	else if (!ft_strncmp(">>", str, 2))
		ft_printf_e("minishell: %s `>>'\n", SYNTAX_ERR);
	else if (!ft_strncmp(">", str, 1))
		ft_printf_e("minishell: %s `>'\n", SYNTAX_ERR);
	else
		ft_printf_e("minishell: %s `newline'\n", SYNTAX_ERR);
	g_error = 1;
	return (-1);
}

static void	initialize_start(char *str, int *i, int *start)
{
	while (str[*i] && str[*i] == ' ')
		(*i)++;
	*start = *i;
}

static void	check_option(int option, int *i)
{
	if (option == 3)
		(*i) = (*i) + 1;
}

static int	get_fd_exit(int fd, char **file_name)
{
	free(*file_name);
	return (fd);
}

int			get_fd(char *str, int option)
{
	char		*file_name;
	int			start;
	int			i;
	int			fd;

	i = 1;
	check_option(option, &i);
	fd = 0;
	initialize_start(str, &i, &start);
	if (ft_strchr("<>", str[i]))
		return (handle_file_name_error(str + i - 1));
	while (str[i] && str[i] != ' ')
		i++;
	file_name = ft_substr(str, start, i - start);
	if (option == 1)
		fd = open(file_name, O_RDONLY);
	else if (option == 2)
		fd = open(file_name, O_RDWR | O_CREAT | O_TRUNC,
			S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	else if (option == 3)
		fd = open(file_name, O_RDWR | O_CREAT | O_APPEND,
			S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	if (fd == -1)
		ft_printf_e("minishell: %s: %s\n", file_name, strerror(errno));
	return (get_fd_exit(fd, &file_name));
}
