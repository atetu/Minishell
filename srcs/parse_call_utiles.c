/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_call_utiles.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thgermai <thgermai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/24 15:55:52 by atetu             #+#    #+#             */
/*   Updated: 2020/09/03 15:24:35 by thgermai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int		handle_file_name_error(char *str)
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
	return (-1);
}

int		get_fd(char *str, int option)
{
	char		*file_name;
	int			start;
	int			i;
	int			fd;

	i = 1;
	if (option == 3)
		i++;
	fd = 0;
	while (str[i] && str[i] == ' ')
		i++;
	start = i;
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
	free(file_name);
	return (fd);
}
