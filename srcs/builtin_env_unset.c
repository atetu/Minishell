/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env_unset.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atetu <atetu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/24 17:59:26 by atetu             #+#    #+#             */
/*   Updated: 2020/08/24 17:59:47 by atetu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void		unset_env_var(char *key)
{
	if (!(ft_strncmp(key, "PWD=", 5)))
	{
		free(g_pwd);
		g_pwd = ft_strdup("");
	}
	if (!(ft_strncmp(key, "OLDPWD=", 8)))
	{
		free(g_oldpwd);
		g_oldpwd = ft_strdup("");
	}
}

static void		unset_error_message(char c)
{
	ft_printf_e("bash: line 1: unset: "); // minishell: unset:
	ft_printf_e("`%c': not a valid identifier\n", c);
}

int			ft_unset(t_call *call, char **func)
{
	int			i;
	char		*key;
	int			j;

	i = 0;
	while (func[++i])
	{
		j = -1;
		while (func[i][++j])
		{
			if (!ft_isalnum((int)func[i][j]) && func[i][j] != '_')
			{
				unset_error_message(func[i][j]);
				return ((g_exit_nb = EXIT_FAILURE));
			}
		}
		key = ft_strjoin(func[i], "=");
		unset_env_var(key);
		if (find_value(key, call->env, 1))
			delete_element(call, key);
		if (find_value(key, call->env, 2))
			delete_element(call, func[i]);
		free(key);
	}
	return (EXIT_SUCCESS);
}
