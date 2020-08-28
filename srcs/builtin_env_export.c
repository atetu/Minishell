/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env_export.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/24 18:02:17 by atetu             #+#    #+#             */
/*   Updated: 2020/08/28 15:11:23 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int		check_export_errors(char *func)
{
	int			i;

	if (func[0] == '=' || func[0] == '+')
	{
		ft_printf_e("minishell : export: ");
		ft_printf_e("`%c': not a valid identifier\n", func[0]);
		return (EXIT_FAILURE);
	}
	i = 0;
	while (func[i] && func[i] != '=')
	{
		if (func[i] == '+' && func[i + 1] == '=')
			;
		else if (!ft_isalnum((int)func[i]) && func[i] != '_' && func[i] != '+')
		{
			ft_printf_e("minishell : export: ");
			ft_printf_e("`%c': not a valid identifier\n", func[i]);
			return ((g_exit_nb = EXIT_FAILURE));
		}
		i++;
	}
	return (EXIT_SUCCESS);
}

static void		export_alone(char *str, t_call *call)
{
	if (str == NULL)
		ft_env1(call);
}

static char		*delete_plus(char *str)
{
	char		*new_str;
	int			i;

	if (!(new_str = malloc(sizeof(char) * (ft_strlen(str)))))
		return (NULL);
	i = -1;
	while (++i < (int)ft_strlen(str) - 2)
		new_str[i] = str[i];
	new_str[i] = '=';
	new_str[i + 1] = '\0';
	return (new_str);
}

static void		check_add_env(char **func, int i, t_call *call, char *key)
{
	if (ft_strchr(func[i], '='))
		add_env(call, key, ft_strchr(func[i], '=') + 1, 1);
}

int				ft_export(t_call *call, char **func)
{
	int			i;
	char		*key;

	i = 0;
	export_alone(func[1], call);
	while (func[++i])
	{
		if (check_export_errors(func[i]))
			return (EXIT_FAILURE);
		if (func[i][0] != '=')
		{
			key = get_key(func[i]);
			if (key[ft_strlen(key) - 2] == '+')
				add_env2(call, delete_plus(key), ft_strchr(func[i], '=') + 1);
			else if (find_value(key, call->env, 1))
				check_add_env(func, i, call, key);
			else if (ft_strchr(func[i], '='))
				add_env(call, key, ft_strchr(func[i], '=') + 1, 0);
			else
				add_env(call, func[i], "\0", 0);
			free(key);
		}
	}
	return (EXIT_SUCCESS);
}
