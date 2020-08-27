/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_global_var_validity.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/27 11:20:49 by user42            #+#    #+#             */
/*   Updated: 2020/08/27 11:51:24 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int			check_parenthesis(char **str, int i)
{
	if ((*str)[i + 1] == ')')
	{
		ft_printf_e("minishell: ");
		ft_printf_e("erreur de syntaxe près du symbole inattendu « ) »\n");
		free(*str);
		*str = NULL;
		return (1);
	}
	else if (((*str)[i + 1]) == '(')
	{
		ft_printf_e("minishell: parenthese non fermee\n");
		free(*str);
		*str = NULL;
		return (1);
	}
	else if (((*str)[i + 1]) == '[')
	{
		ft_printf_e("minishell: crochet non ferme\n");
		free(*str);
		*str = NULL;
		return (1);
	}
	return (0);
}

char		*clean_parse_var(char **str)
{
	free(*str);
	return (ft_strdup("\x80\xf5"));
}

char		*check_validity(char *str, int i, t_list **env)
{
	int			error;

	error = 0;
	if (str[i + 1] == '{')
	{
		if (!(str = fill_var2(str, i, env)))
			return (NULL);
	}
	else if (check_weird_char(&str, i, &error))
	{
		if (error)
			return (NULL);
	}
	else if (check_parenthesis(&str, i))
		return (NULL);
	else
		str = fill_var1(str, i, env);
	return (str);
}
