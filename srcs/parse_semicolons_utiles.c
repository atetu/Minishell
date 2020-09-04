/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_semicolons_utiles.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/04 13:38:51 by user42            #+#    #+#             */
/*   Updated: 2020/09/04 13:41:23 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int		syntax_error(char **str)
{
	free(*str);
	g_exit_status = 2;
	g_exit_nb = 2;
	ft_printf_e("minihell: syntax error near unexpected token ';'\n");
	return (-1);
}

int		result_semicolon(char **temp, int option, int n_semicolon)
{
	free(*temp);
	if (option == 1)
		return (-1);
	return (n_semicolon);
}

int		exit_get_n_semicolon(char **temp, int i)
{
	free(*temp);
	return (i);
}

int		go_backward(char *args, int i)
{
	int	j;

	j = i - 1;
	while (j >= 0 && args[j] == ' ')
		j--;
	return (j);
}
