/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_semicolons.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/01 15:24:14 by atetu             #+#    #+#             */
/*   Updated: 2020/09/07 15:05:46 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int		get_n_semicolon(char *args, int option)
{
	int			i;
	int			n_semicolon;
	int			j;
	char		*temp;

	parse_backslash((temp = ft_strdup(args)));
	i = -1;
	n_semicolon = 0;
	while (temp[++i])
	{
		if (temp[i] == ';' && !is_valide(temp, i, 1) && (i == 0 ||
		(i > 0 && temp[i - 1] != -1)))
		{
			if (option == 1)
				return (exit_get_n_semicolon(&temp, i));
			if (i > 0)
			{
				j = go_backward(args, i);
				if (args[j] == '>' || args[j] == '<')
					return (syntax_error(&temp));
			}
			n_semicolon++;
		}
	}
	return (result_semicolon(&temp, option, n_semicolon));
}

static void		check_pipes(char **tab, int i, char *s, int *pipe)
{
	int j;
	int x;

	j = -1;
	if (!s && *pipe)
		return ;
	while (tab[++j] && j <= i)
	{
		if (ft_strnstr(tab[j], "||", ft_strlen(tab[j])))
		{
			error_pipe(pipe);
			return ;
		}
		x = 0;
		while (tab[j][x] == ' ')
			x++;
		if (tab[j][x] == '|')
		{
			error_pipe(pipe);
			return ;
		}
	}
	error_semi(s);
}

static void		free_tab(char ***tab, int n_semicolons)
{
	free((*tab)[n_semicolons + 1]);
	free((*tab)[n_semicolons]);
	(*tab)[n_semicolons] = NULL;
}

static char		**check_args(char **tab, int n_semicolons)
{
	int			i;
	int			pipe;

	i = -1;
	pipe = 0;
	while (tab[++i + 1])
	{
		if (tab[i + 1] && !ft_strlen(tab[i + 1]) && i < n_semicolons - 1)
		{
			check_pipes(tab, i, ";;", &pipe);
			break ;
		}
		else if (!ft_strlen(tab[i]) || !arg_is_valid(tab[i]))
		{
			check_pipes(tab, i, ";", &pipe);
			break ;
		}
	}
	if (!ft_strlen(tab[n_semicolons]) && i == n_semicolons && !pipe)
	{
		check_pipes(tab, i, NULL, &pipe);
		if (!pipe)
			free_tab(&tab, n_semicolons);
	}
	return (handle_error_arg(i, n_semicolons, tab, pipe));
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
	tab = check_args(tab, n_semicolons);
	return (tab);
}
