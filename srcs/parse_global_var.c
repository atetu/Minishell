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

static char		*fill_var1(char *str, int index, t_list **env)
{
	char		*key;
	char		*value;
	char		*new_str;

	if (!(key = get_var_name(&str[index + 1])))
		return (str);
	value = get_var_value(key, env);
//	ft_printf("key: %s\n", key);
	new_str = create_new_str(str, key, value, index);
	free(key);
	free(value);
	free(str);
	return (new_str);
}

static char		*fill_var2(char *str, int index, t_list **env)
{
	char		*key;
	char		*value;
	char		*new_str;
	int			close;

	close = 0;
	key = get_var_name(&str[index + 2]);
	if (str[index + ft_strlen(key) + 1] == '}')
		close = 1;
	if (!close)
	{
		free(key);
		free(str);
		//ft_printf_e("Minishell: unexpected EOF while looking for matching }\n");
		ft_printf_e("Minishell: erreur : absence de }\n");
		return (NULL);
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
			str[i + 1] == '(' || str[i + 1] == '-')) //ICI
		return (1);
	return (0);
}

int 			check_weird_char(char **str, int i)
{
	char *key;
	char *value;
	char *new_str;
//	char *new_str;

//	new_str = NULL;
	if ((*str)[i + 1] == '!'|| (*str)[i + 1] == '@' || (*str)[i + 1] == '*'
		|| ((*str)[i + 1] == '(' && (*str)[i + 2] && (*str[i + 2] == '0'))
		|| (*str)[i + 1] == '-')
	{
		if ((*str)[i + 1] == '!')
			key = ft_strdup("!=");
		if ((*str)[i + 1] == '@')
			key = ft_strdup("!=");
		if ((*str)[i + 1] == '*')
			key = ft_strdup("!=");
		if ((*str)[i + 1] == '-')
			key = ft_strdup("hBs");
		if ((*str)[i + 1] == '(' && (*str)[i + 2] && (*str[i + 2] == '0'))
			key = ft_strdup("()=");
		value = ft_strdup ("");
		new_str = create_new_str(*str, key, value, i);
		free(key);
		free(value);
		free(*str);
		*str = new_str;
		return (1);
	}
	return (0);
}

char			*parse_var(char *str, t_list **env)
{
	int			i;

	i = -1;
	ft_printf("str: %s\n", str);
	while (str[++i])
	{
		if (is_correct(str, i))
		{
			if (str[i + 1] == '{')
			{
				if (!(str = fill_var2(str, i, env)))
					return (NULL);
			}
			else if (check_weird_char(&str, i))
			{
			//	ft_printf("ici");
				// char *key;
				// char *value;
				// char *new_str;

				// key = ft_strdup("!=");
				// value = ft_strdup ("");
				// new_str = create_new_str(str, key, value, i);
				// free(key);
				// free(value);
				// free(str);
				// str = new_str;
			}
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
