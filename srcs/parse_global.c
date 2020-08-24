/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_global.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atetu <atetu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/17 14:48:07 by thgermai          #+#    #+#             */
/*   Updated: 2020/08/24 17:21:45 by atetu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void		handle_empty_arg(char **arg, int *n, int *n_args)
{
	free(*arg);
	*arg = NULL;
	*n = *n - 1;
	*n_args = *n_args - 1;
}

static int		create_tab(char *str, char **tab, t_list **env, int n_args)
{
	int			n;
	int			i;

	n = 0;
	while (n < n_args)
	{
		i = -1;
		while (*str == ' ')
			str++;
		while (str[++i])
			if (str[i] == ' ' && !is_valide(str, i, 1))
				break ;
		if (!(tab[n++] = parse_arg(ft_substr(str, 0, i), env)))
		{
			clean_array(tab);
			return (0);
		}
		if (!ft_strncmp(tab[n - 1], "\x80\xf5", 3))
			handle_empty_arg(&tab[n - 1], &n, &n_args);
		str = str + i;
	}
	tab[n] = NULL;
	return (1);
}

static void		replace_g_last(char **last, char *last_arg)
{
	free(*last);
	*last = ft_strdup(last_arg);
}

char			**parse(char *str, t_list **env)
{
	char		**tab;
	int			n_args;
	int			i;

	if (!str || !ft_strlen(str))
		return (NULL);
	parse_backslash(str);
	n_args = get_n_args(str) + 1;
	if (!(tab = malloc(sizeof(char *) * (n_args + 1))))
		return (NULL);
	if (!(create_tab(str, tab, env, n_args)))
		return (NULL);
	i = 0;
	while (tab[i])
		i++;
	replace_g_last(&g_last, tab[i - 1]);
	return (tab);
}
