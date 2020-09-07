/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_semicolons_utiles.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/04 13:38:51 by user42            #+#    #+#             */
/*   Updated: 2020/09/07 15:14:37 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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

void	exit_status_nb(void)
{
	g_exit_status = 2;
	g_exit_nb = g_exit_status;
}
