/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_test.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atetu <atetu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/17 14:48:07 by thgermai          #+#    #+#             */
/*   Updated: 2020/08/24 11:54:04 by atetu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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
		ft_printf_e("Minishell: error: arguments not closed\n");
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

static void		parse_backslash(char *str)
{
	int			i;
	int			in_quote;
	int			in_dquote;

	in_quote = 0;
	in_dquote = 0;
	i = -1;
	while (str[++i])
	{
		if (str[i] == '"' &&
			(i == 0 || (i > 0 && str[i - 1] != -1)) && !in_quote)
			in_dquote == 1 ? in_dquote-- : in_dquote++;
		else if (str[i] == '\'' &&
			(i == 0 || (i > 0 && str[i - 1] != -1)) && !in_dquote)
			in_quote == 1 ? in_quote-- : in_quote++;
		if (str[i] == '\\' && (i == 0 || (i > 0 && str[i - 1] != -1)))
		{
			if (!in_quote && !in_dquote)
				str[i] = -1;
			else if (in_dquote && str[i + 1] && ft_strchr("$\\\"", str[i + 1]))
				str[i] = -1;
		}
	}
}

static void		parse_quotes(char *str)
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

static char		*get_var_name(char *str)
{
	int			i;
	char		*var_name;
	
	i = -1;
	if (str[0] == '?')
		return (ft_strdup("?="));
	if (!ft_isalpha(str[0]) && str[0] != '_')
	{
	//	printf("str: %s\n", str);fflush(stdout);
	// 	char *result;
	// 	result = malloc(sizeof(char) * 3);
	// 	result[0] = '0';
	// 	result[1] = '0';
	// 	result[2] = '\0';
	// //	result = ft_strdup("00");
	// 	return (result);
		return (ft_strdup("00"));
	}
	while (str[++i])
		if (!ft_isalnum(str[i]) && str[i] != '_')
			break ;
	if (!(var_name = malloc(sizeof(char) * (i + 2))))
		return (NULL);
	var_name[i + 1] = '\0';
	var_name[i] = '=';
	while (i-- > 0)
		var_name[i] = str[i];
	return (var_name);
}

static char		*get_var_value(char *key, t_list **env)
{
	char		*value;

	if (!ft_strncmp(key, "00", 3))
		value = ft_strdup("");
	else if (key[0] == '?' && ft_strlen(key) == 2)
		value = ft_itoa(g_exit_status);
	else if (!ft_strncmp(key, "_=", 3))
		value = ft_strdup(g_last);
	else if (find_value(key, env, 1))
		value = ft_strdup(find_value(key, env, 1) + ft_strlen(key));
	else
		value = ft_strdup("");
	return (value);
}

static char		*create_new_str(char *str, char *key, char *value, int index)
{
	char		*new_str;
	char		*after_var;

	if (ft_strlen(str) - ft_strlen(key) + ft_strlen(value) == 0)
		new_str = ft_strdup("");
	else if (!(new_str = malloc(sizeof(char) * (ft_strlen(str) -
		ft_strlen(key) + ft_strlen(value) + 1 ))))  //ICICICI!!!
		return (NULL);
	ft_strlcpy(new_str, str, index + 1);
	ft_strlcpy(new_str + ft_strlen(new_str), value, ft_strlen(value) + 1);
	after_var = &str[index + ft_strlen(key)];
	ft_strlcpy(new_str + ft_strlen(new_str), after_var,
		ft_strlen(after_var) + 1);
	return (new_str);
}

static char		*fill_var1(char *str, int index, t_list **env)
{
	char		*key;
	char		*value;
	char		*new_str;
	// char		*to_find;
	// char		*copy; //ICI

	new_str = NULL;
	// copy = NULL;
	// to_find = NULL;
	// copy = ft_strdup(str);
	// to_find = ft_strdup(&copy[index + 1]);
	//printf("str: %s\n", str);fflush(stdout);
	//printf("to find: %s\n", to_find);fflush(stdout);
	// if (!(key = get_var_name(to_find)))
	// {	
	// 	free(to_find);
	// 	free(copy);
	// 	return (str);
	// }
	// free(to_find);
	// free(copy);
	//printf("str2: %s\n\n", str);fflush(stdout);
	if (!(key = get_var_name(&str[index + 1])))
	 	return (str);
	value = get_var_value(key, env);
	new_str = create_new_str(str, key, value, index);
	free(key);
	free(value);
	free(str);
	return (new_str);
}

static char		*create_new_str2(char *str, char *key, char *value, int index)
{
	char		*new_str;
	char		*after_var;

	if (!(new_str = malloc(sizeof(char) * (ft_strlen(str) - ft_strlen(key) +
		ft_strlen(value)))))
		return (NULL);
	ft_strlcpy(new_str, str, index + 1);
	ft_strlcpy(new_str + ft_strlen(new_str), value, ft_strlen(value) + 1);
	after_var = str + index + ft_strlen(key) + 2;
	ft_strlcpy(new_str + ft_strlen(new_str), after_var,
		ft_strlen(after_var) + 1);
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
		ft_printf_e("Minishell: unexpected EOF while looking for matching }\n");
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

	if (!(new_str = malloc(sizeof(char) * (ft_strlen(str) - 1 +
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
			str[i + 1] == '_' || str[i + 1] == '{' || str[i + 1] == '?'))
		return (1);
	return (0);
}

static char		*parse_var(char *str, t_list **env)
{
	int			i;

	i = -1;
	while (str[++i])
	{
		if (is_correct(str, i))
		{
			if (str[i + 1] == '{')
			{
				if (!(str = fill_var2(str, i, env)))
					return (NULL);
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

static char		*delete_marks(char *str, int j)
{
	int			i;
	char		*new_str;

	if (!(new_str = malloc(sizeof(char) * (j + 1))))
		return (NULL);
	i = -1;
	j = 0;
	while (str[++i])
	{
		if (str[i] < 0)
			;
		else
			new_str[j++] = str[i];
	}
	new_str[j] = '\0';
	return (new_str);
}

static char		*replace_marks(char *str)
{
	int			i;
	int			j;
	char		*new_str;

	i = -1;
	j = 0;
	while (str[++i])
		if (str[i] > 0)
			j++;
	if (!j)
	{
		free(str);
		return (ft_strdup(""));
	}
	new_str = delete_marks(str, j);
	free(str);
	return (new_str);
}

static char		*parse_arg(char *str, t_list **env)
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

static int		get_n_args(char *str)
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

static void		replace_g_last(char **last, char *last_arg)
{
	free(*last);
	*last = ft_strdup(last_arg);
}

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
