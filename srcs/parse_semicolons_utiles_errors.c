/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_semicolons_utiles_errors.c                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/07 15:05:19 by user42            #+#    #+#             */
/*   Updated: 2020/09/07 15:14:11 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	**handle_error_arg(int i, int n_semicolons, char **tab,
					int pipe)
{
	if (i < n_semicolons || pipe)
	{
		i = -1;
		while (tab[++i])
			free(tab[i]);
		free(tab);
		return (NULL);
	}
	return (tab);
}

void	error_semi(char *s)
{
	if (s)
		ft_printf_e("minishell: syntax error near unexpected token `%s'\n", s);
	exit_status_nb();
}

void	error_pipe(int *pipe)
{
	*pipe = 1;
	ft_printf_e("minishell: syntax error near unexpected token `|'\n");
	exit_status_nb();
}

int		syntax_error(char **str)
{
	free(*str);
	g_exit_status = 2;
	g_exit_nb = 2;
	ft_printf_e("minihell: syntax error near unexpected token ';'\n");
	return (-1);
}
