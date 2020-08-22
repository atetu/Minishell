/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thgermai <thgermai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/29 21:54:49 by thgermai          #+#    #+#             */
/*   Updated: 2020/08/22 14:54:53 by thgermai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int				ft_echo(char **func)
{
	int			i;
	int			space;

	i = 0;
	space = 1;
	while (func[++i])
	{
		if (ft_strncmp(func[i], "-n", 3) == 0)
			space = 0;
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

void	handle_env_var(t_call *call)
{
	char	buf[512];   // pour stocker variable globale

	free(g_oldpwd);  //ICI
	g_oldpwd = ft_strdup(g_pwd);  // ICI on copie pwd dans oldpwd
	free(g_pwd);
	g_pwd = ft_strdup(getcwd(buf, 512));  // ICI on met le nouveau chemin dans pwd
	if (find_value("PWD=", call->env, 1) || find_value("PWD=", call->env, 2)) //on verifie presence dans var env et dans var exportet si presence on modifie
		add_env(call, "PWD=", g_pwd, 1);
	if (find_value("OLDPWD=", call->env, 1) ||
	find_value("OLDPWD=", call->env, 2))
		add_env(call, "OLDPWD=", g_oldpwd, 1);
}

int				ft_cd(char **func, t_call *call)
{
	int		i;

	i = 0;
	if (func[1] && chdir(func[1]) == -1)
	{
		ft_printf_e("bash: line 1: cd: %s: %s\n", func[1], strerror(errno));  // JUSTE POUR LES TESTS
	//	ft_printf_e("minishell: cd: %s: %s\n", func[1], strerror(errno));
	//  ft_printf_e("bash: ligne 1 : cd: %s: Aucun fichier ou dossier de ce type\n", func[1]);i // VM Testeur
	//  ft_printf_e("minishell: cd: %s: Aucun fichier ou dossier de ce type\n", func[1]);i // VM Testeur
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
		//ft_printf_e("Minishell: error: %s\n", strerror(errno));
		ft_printf_e("bash: line 1: error: %s\n", strerror(errno));             //JUSTE POUR LE TESTS!!!
		return (EXIT_FAILURE);
	}
	ft_printf("%s\n", current);
	return (EXIT_SUCCESS);
}
