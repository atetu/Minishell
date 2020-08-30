/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/29 21:54:49 by thgermai          #+#    #+#             */
/*   Updated: 2020/08/30 12:56:35 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int		check_flag(char **func, int i)
{
	if (i == 1 && !ft_strncmp(func[1], "-n", 3))
		return (1);
	if (i > 1)
	{
		if (!ft_strncmp(func[i], "-n", 3))
		{
			while (i > 1)
			{
				if (ft_strncmp(func[i], "-n", 3))
					break ;
				i--;
			}
			if (i == 1)
				return (1);
			return (0);
		}
	}
	return (0);
}

int				ft_echo(char **func)
{
	int			i;
	int			space;

	i = 0;
	space = 1;
	if (func[1] && ft_strncmp(func[1], "-n", 3) == 0)
		space = 0;
	while (func[++i])
	{
		if (check_flag(func, i))
			;
		else
		{
			if (write(1, func[i], ft_strlen(func[i])) == -1)
			{
				ft_printf_e("%s\n", strerror(errno));
				return (EXIT_FAILURE);
			}
			if (func[i + 1])
				write(1, " ", 1);
		}
	}
	if (space)
		write(1, "\n", 1);
	return (EXIT_SUCCESS);
}

static void		handle_env_var(t_call *call)
{
	char	buf[512];

	free(g_oldpwd);
	g_oldpwd = ft_strdup(g_pwd);
	free(g_pwd);
	g_pwd = ft_strdup(getcwd(buf, 512));
	if (find_value("PWD=", call->env, 1) || find_value("PWD=", call->env, 2))
		add_env(call, "PWD=", g_pwd, 1);
	if (find_value("OLDPWD=", call->env, 1) ||
	find_value("OLDPWD=", call->env, 2))
		add_env(call, "OLDPWD=", g_oldpwd, 1);
}

int				ft_cd(char **func, t_call *call)
{
	int		i;

	i = 0;
	if (func[1] && func[2])
	{
		ft_printf_e("minishell: cd: too many argments\n");
		return (EXIT_FAILURE);
	}
	else if (func[1] && chdir(func[1]) == -1)
	{
		ft_printf_e("minishell: cd: %s: %s\n", func[1], strerror(errno));
		return (EXIT_FAILURE);
	}
	else if (!func[1])
	{
		if (call->env)
		{
			if (chdir(g_home) == -1)
				return (EXIT_FAILURE);
		}
	}
	handle_env_var(call);
	return (EXIT_SUCCESS);
}

int				ft_pwd(void)
{
	char		buf[512];
	char		*current;

	if ((current = getcwd(buf, 512)) == NULL)
	{
		ft_printf_e("minishell: error: %s\n", strerror(errno));
		return (EXIT_FAILURE);
	}
	ft_printf("%s\n", current);
	return (EXIT_SUCCESS);
}
