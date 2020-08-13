/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_func.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atetu <atetu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/24 11:30:16 by thgermai          #+#    #+#             */
/*   Updated: 2020/08/13 11:48:07 by atetu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int		get_n_args(char *str)
{
	int				count;
	int				i;
	int				in_quote;
	int				in_dquote;

	count = 0;
	i = -1;
	in_quote = 0;
	in_dquote = 0;
	while (str[++i] == ' ')
		;
	while (str[++i])
	{
		if (str[i] == ' ' && str[i + 1] && str[i + 1]
			!= ' ' && !is_valide(str, i, 1))
			count++;
	}
	return (count);
}

static int		create_line(char *str, char **tab)
{
	int			i;
	int			in_quote;
	int			in_dquote;

	in_quote = 0;
	in_dquote = 0;
	i = -1;
	while (str[++i])
	{
		if (str[i] == '\'' || str[i] == '"')
		{
			if (i > 0 && !in_quote && is_backslash(str, i - 1))
				;
			else if (str[i] == '"' && !in_quote)
				in_dquote == 1 ? in_dquote-- : in_dquote++;
			else if (str[i] == '\'' && !in_dquote)
				in_quote == 1 ? in_quote-- : in_quote++;
		}
		if ((str[i] == ' ' || !str[i + 1]) && !in_quote && !in_dquote)
		{
			!str[i + 1] && str[i] != ' ' ? i++ : (void)i;
			return (ft_strlen((*tab = ft_substr(str, 0, i))));
		}
	}
	return (i);
}

static int		check_closed(char *str)
{
	int			i;
	int			in_quote;
	int			in_dquote;

	in_quote = 0;
	in_dquote = 0;
	i = -1;
	while (str[++i])
	{
		if (str[i] == '\'' || str[i] == '"')
		{
			if (i > 0 && !in_quote && is_backslash(str, i - 1))
				;
			else if (str[i] == '\'' && !in_dquote)
				in_quote == 1 ? in_quote-- : in_quote++;
			else if (str[i] == '"' && !in_quote)
				in_dquote == 1 ? in_dquote-- : in_dquote++;
		}
	}
	if (in_dquote || in_quote)
	{
		ft_printf_e("Minishell: error: arguments not closed\n");
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

char			**parse_func(char *str, t_list **env)
{
	int				size;
	int				i;
	char			**tab;

	i = -1;
	if (!str || !ft_strlen(str))
		return (NULL);
	if (check_closed(str))
		return (NULL);
	size = get_n_args(str) + 1;
	if (!(tab = malloc(sizeof(char *) * (size + 1))))
		return (NULL);
	while (++i < size)
	{		
		while (*str == ' ')
			str++;
		str = str + create_line(str, &tab[i]);
		tab[i] = parse_var(tab[i], tab[0], env);               /////icicicicici pour echo $PWD
		tab[i] = parse_quotes(tab[i]);
		tab[i] = parse_tilde(tab[i], env);
	}	
	tab[i] = NULL;
	return (tab);
}
