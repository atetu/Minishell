/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_global_args.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/24 17:30:13 by atetu             #+#    #+#             */
/*   Updated: 2020/08/28 14:52:57 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int		check_closed(char *str)
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
			if (i > 0 && str[i - 1] == -1)
				;
			else if (str[i] == '\'' && !in_dquote)
				in_quote == 1 ? in_quote-- : in_quote++;
			else if (str[i] == '"' && !in_quote)
				in_dquote == 1 ? in_dquote-- : in_dquote++;
		}
	}
	if (in_dquote || in_quote)
	{
		ft_printf_e("minishell: error: arguments not closed\n");
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

void	parse_quotes(char *str)
{
	int			i;
	int			in_quote;
	int			in_dquote;

	in_quote = 0;
	in_dquote = 0;
	i = -1;
	while (str[++i])
	{
		if (i > 0 && str[i - 1] == -1)
			;
		else if (str[i] == '\'' && !in_dquote)
		{
			in_quote == 1 ? in_quote-- : in_quote++;
			str[i] = -2;
		}
		else if (str[i] == '"' && !in_quote)
		{
			in_dquote == 1 ? in_dquote-- : in_dquote++;
			str[i] = -2;
		}
	}
}

char	*parse_arg(char *str, t_list **env)
{
	if (check_closed(str))
	{
		free(str);
		return (NULL);
	}
	if (!(str = parse_var(str, env)))
		return (NULL);
	if (ft_strncmp(str, "\x80\xf5", ft_strlen(str)))
	{
		parse_quotes(str);
		str = replace_marks(str);
	}
	return (str);
}

int		get_n_args(char *str)
{
	int				count;
	int				i;

	count = 0;
	i = -1;
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
