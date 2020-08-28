/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_global_var_weird.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/27 11:22:39 by user42            #+#    #+#             */
/*   Updated: 2020/08/28 15:01:31 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int			check_first_weird_char(char c, char **key, char **value)
{
	if (c == '!')
	{
		*key = ft_strdup("!=");
		return (1);
	}
	else if (c == '@')
	{
		*key = ft_strdup("!=");
		return (1);
	}
	else if (c == '*')
	{
		*key = ft_strdup("!=");
		return (1);
	}
	else if (c == '-')
	{
		*key = ft_strdup("-=");
		*value = ft_strdup("hBs");
		return (1);
	}
	return (0);
}

int			check_second_weird_char(char *str, int i,
				char **key, char **value)
{
	if (str[i + 1] == '#')
	{
		*key = ft_strdup("#=");
		*value = ft_strdup("0");
		return (1);
	}
	else if (str[i + 1] == '(' && str[i + 2]
		&& str[i + 2] == ')')
	{
		*key = ft_strdup("()=");
		return (1);
	}
	return (0);
}

int			check_third_weird_char_parenthesis(char *str, int i, int **error)
{
	int j;

	j = i + 2;
	while (str[j] && str[j] != ')')
		j++;
	if (!is_valide(str, j, 0) && str[j - 1] != -1)
	{
		**error = 1;
		ft_printf_e("minishell: error: parenthesis after $ sign\n");
		return (1);
	}
	else
		return (0);
}

int			check_weird_char(char **str, int i, int *error)
{
	char *key;
	char *value;
	char *new_str;

	key = NULL;
	value = NULL;
	if (check_first_weird_char((*str)[i + 1], &key, &value))
		;
	else if (check_second_weird_char(*str, i, &key, &value))
		;
	else if (((*str)[i + 1]) == '(' && ((*str)[i + 2])
		&& ((*str)[i + 2] == ')'))
		key = ft_strdup("()=");
	else if (((*str)[i + 1]) == '[' && ft_strchr(&((*str)[i + 1]), ']'))
	{
		if (!(handle_brackets(*str, i, &key, &value)))
			return (0);
	}
	else if (((*str)[i + 1]) == '(' && ft_strchr(&((*str)[i + 1]), ')'))
		return (check_third_weird_char_parenthesis(*str, i, &error));
	else
		return (0);
	check_null_value(&value);
	new_str = create_new_str(*str, key, value, i);
	return (clean_weird(&key, &value, &str, &new_str));
}
