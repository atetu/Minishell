/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_semicolons.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/01 15:24:14 by atetu             #+#    #+#             */
/*   Updated: 2020/08/28 15:02:13 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int		syntax_error(void)
{
	g_exit_status = 258;
	g_exit_nb = 2;
	ft_printf_e("minihell: syntax error near unexpected token ';'\n");
	return (-1);
}

static int		result_semicolon(int option, int n_semicolon)
{
	if (option == 1)
		return (-1);
	return (n_semicolon);
}

static int		get_n_semicolon(char *args, int option)
{
	int			i;
	int			n_semicolon;
	int			j;

	i = 0;
	n_semicolon = 0;
	while (args[++i])
	{
		if (args[i] == ';' && !is_valide(args, i, 1) && (i == 0 ||
		(i > 0 && !is_backslash(args, i - 1))))
		{
			if (option == 1)
				return (i);
			if (i > 0)
			{
				j = i - 1;
				while (j >= 0 && args[j] == ' ')
					j--;
			}
			if (args[j] == '>' || args[j] == '<')
				return (syntax_error());
			n_semicolon++;
		}
	}
	return (result_semicolon(option, n_semicolon));
}

char			**parse_semicolon(char *str)
{
	int			i;
	int			j;
	int			last_i;
	char		**tab;
	int			n_semicolons;

	last_i = 0;
	i = 0;
	j = 0;
	if ((n_semicolons = get_n_semicolon(str, 0)) == -1)
		return (NULL);
	if (!(tab = malloc(sizeof(char *) * (n_semicolons + 2))))
		return (NULL);
	while (get_n_semicolon(str + last_i, 1) != -1)
	{
		tab[j] = ft_substr(str + last_i, 0,
			get_n_semicolon(str + last_i, 1));
		last_i += ft_strlen(tab[j]) + 1;
		i++;
		j++;
	}
	tab[j] = ft_substr(str + last_i, 0, ft_strlen(str + last_i));
	tab[j + 1] = NULL;
	return (tab);
}
