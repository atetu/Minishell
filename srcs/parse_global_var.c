/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_global_var.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atetu <atetu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/24 17:30:37 by atetu             #+#    #+#             */
/*   Updated: 2020/08/25 10:41:32 by atetu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "stdio.h"
#include "stdlib.h"

static char		*fill_var1(char *str, int index, t_list **env)
{
	char		*key;
	char		*value;
	char		*new_str;

	if (!(key = get_var_name(&str[index + 1])))
		return (str);
	value = get_var_value(key, env);
	new_str = create_new_str(str, key, value, index);
	free(key);
	free(value);
	free(str);
	return (new_str);
}

char			*fill_var2_error(char **str, int option)
{
	free(*str);
	if (option == 1)
		ft_printf_e("Minishell: erreur : absence de }\n");
	else if (option == 2)
		ft_printf_e("minishell: ${} : mauvaise substitution\n");
	else if (option == 3)
		ft_printf_e("Minishell: erreur : absence de }\n");
	return (NULL);
}

static char		*fill_var2(char *str, int index, t_list **env)
{
	char		*key;
	char		*value;
	char		*new_str;
	int			close;

	close = 0;
	if (!str[index + 2])
		return (fill_var2_error(&str, 1));
	if (str[index + 2] == '}')
		return (fill_var2_error(&str, 2));
	key = get_var_name(&str[index + 2]);
	if (str[index + ft_strlen(key) + 1] == '}')
		close = 1;
	if (!close)
	{
		free(key);
		return (fill_var2_error(&str, 3));
	}
	value = get_var_value(key, env);
	new_str = create_new_str2(str, key, value, index);
	free(key);
	free(value);
	free(str);
	return (new_str);
}

static char		*fill_tilde(char *str, int index)
{
	char		*new_str;
	char		*after_var;

	if (!(new_str = malloc(sizeof(char) * (ft_strlen(str) +
		ft_strlen(g_home)))))
		return (NULL);
	ft_strlcpy(new_str, str, index + 1);
	ft_strlcpy(new_str + ft_strlen(new_str), g_home, ft_strlen(g_home) + 1);
	after_var = ft_strdup(str + index + 1);
	ft_strlcpy(new_str + ft_strlen(new_str), after_var,
		ft_strlen(after_var) + 1);
	free(str);
	free(after_var);
	return (new_str);
}

static int		is_correct(char *str, int i)
{
	if (str[i] == '$' && !is_valide(str, i, 0) && (i == 0 ||
		(i > 0 && str[i - 1] != -1)) && (ft_isalnum(str[i + 1]) ||
		str[i + 1] == '_' || str[i + 1] == '{' || str[i + 1] == '?' ||
		str[i + 1] == '!' || str[i + 1] == '@' || str[i + 1] == '*' || //ICI
		str[i + 1] == '(' || str[i + 1] == '-' || str[i + 1] == ')' ||
		str[i + 1] == '[' || str[i + 1] == '#' || str[i + 1] == '&')) // || str[i + 1] == ']')) //ICI
		return (1);
	return (0);
}

int check_first_weird_char(char c, char **key, char **value)
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

int check_second_weird_char(char *str, int i, char **key, char **value)
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

int handle_brackets(char *str, int i, char **key, char **value)
{
	int j;
	char *tmp;

	tmp = NULL;
	j = i + 2;
	while (str[j] && str[j] != ']')
		j++;
	if (!is_valide(str, j, 0) && str[j - 1] != -1)
	{
		tmp = ft_substr(str, i + 1, j - i);
		*key = ft_strjoin_f1(tmp, "=");
		*value = ft_strdup("0");
		return (1);
	}
	else
		return (0);
}

int				check_weird_char(char **str, int i, int *error)
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
	{
		int j;
		j = i + 2;
		while ((*str)[j] && (*str)[j] != ')')
			j++;
		if (!is_valide(*str, j, 0) && (*str)[j - 1] != -1)
		{
			*error = 1;
			ft_printf_e("minishell: erreur: parentheses apres le signe $\n");
			return (1);
		}
		else
			return (0);
	}
	else
		return (0);
	if (!value)
		value = ft_strdup("");
	new_str = create_new_str(*str, key, value, i);
	free(key);
	free(value);
	free(*str);
	*str = new_str;
	return (1);
}

int				check_parenthesis(char **str, int i)
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

char			*parse_var(char *str, t_list **env)
{
	int			i;
	int			error;

	i = -1;
	error = 0;
	while (str[++i])
	{
		if (is_correct(str, i))
		{
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
			if (!is_valide(str, i, 1) && !ft_strlen(str))
			{
				free(str);
				return (ft_strdup("\x80\xf5"));
			}
			i = -1;
		}
		else if (str[i] == '~' && !is_valide(str, i, 1))
			str = fill_tilde(str, i);
	}
	return (str);
}
