/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_global_var_utiles.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atetu <atetu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/24 17:31:19 by atetu             #+#    #+#             */
/*   Updated: 2020/08/25 10:41:44 by atetu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char		*get_var_name(char *str)
{
	int			i;
	char		*var_name;

	i = -1;
	if (str[0] == '?')
		return (ft_strdup("?="));
	if (str[0] == '0') // ICI
		return (ft_strdup("$0")); //ICI
	if (!ft_isalpha(str[0]) && str[0] != '_')
		return (ft_strdup("00"));
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

char		*get_var_value(char *key, t_list **env)
{
	char		*value;

	if (!ft_strncmp(key, "00", 3))
		value = ft_strdup("");
	if (!(ft_strncmp(key, "$0", 3))) //ICI
		value = ft_strdup("bash"); //ICI
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

char		*create_new_str(char *str, char *key, char *value, int index)
{
	char		*new_str;
	char		*after_var;

	if (ft_strlen(str) - ft_strlen(key) + ft_strlen(value) == 0)
		new_str = ft_strdup("");
	else if (!(new_str = malloc(sizeof(char) * (ft_strlen(str) -
		ft_strlen(key) + ft_strlen(value) + 1))))
		return (NULL);
	ft_strlcpy(new_str, str, index + 1);
	ft_strlcpy(new_str + ft_strlen(new_str), value, ft_strlen(value) + 1);
	after_var = &str[index + ft_strlen(key)];
	ft_strlcpy(new_str + ft_strlen(new_str), after_var,
		ft_strlen(after_var) + 1);
	return (new_str);
}

char		*create_new_str2(char *str, char *key, char *value, int index)
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
