/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd_pwd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/29 21:54:49 by thgermai          #+#    #+#             */
/*   Updated: 2020/09/07 15:22:18 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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

static int		check_path(char **str)
{
	char			buffer[512];
	struct stat		stat_buff;

	if (!ft_strncmp(*str, ".", 2))
	{
		if (!getcwd(buffer, 512))
		{
			ft_printf_e("cd: error retrieving current directory: getcwd: ");
			ft_printf_e("%s: %s\n", PARENT_ERR, strerror(errno));
			return (-1);
		}
	}
	else if (!ft_strncmp(*str, "-", 2))
	{
		free(*str);
		*str = ft_strdup(g_oldpwd);
		if (!stat(g_oldpwd, &stat_buff))
			ft_printf("%s\n", *str);
	}
	return (0);
}

int				ft_cd(char **func, t_call *call)
{
	int		i;

	i = 0;
	if (func[1] && func[2])
	{
		ft_printf_e("minishell: cd: too many arguments\n");
		return (EXIT_FAILURE);
	}
	if (func[1] && check_path(&func[1]) == -1)
		return (EXIT_FAILURE);
	if (func[1] && chdir(func[1]) == -1)
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
