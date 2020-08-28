/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_global_var_fill.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/27 11:30:50 by user42            #+#    #+#             */
/*   Updated: 2020/08/28 14:54:26 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*fill_var1(char *str, int index, t_list **env)
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

char	*fill_var2_error(char **str, int option)
{
	free(*str);
	if (option == 1)
		ft_printf_e("minishell: error : missing '}'\n");
	else if (option == 2)
		ft_printf_e("minishell: ${} : bad substitution\n");
	else if (option == 3)
		ft_printf_e("minishell: error : missing '}'\n");
	return (NULL);
}

char	*fill_var2(char *str, int index, t_list **env)
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

char	*fill_tilde(char *str, int index)
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
