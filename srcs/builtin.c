/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atetu <atetu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/29 21:54:49 by thgermai          #+#    #+#             */
/*   Updated: 2020/08/14 16:08:32 by atetu            ###   ########.fr       */
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

void handle_env_var(t_call *call)
{
	char	buf[512];   // pour stocker variable globale
	
	free(g_oldpwd);  //ICI
	g_oldpwd = ft_strdup(g_pwd);  // ICI on copie pwd dans oldpwd
	free(g_pwd);
	g_pwd = ft_strdup(getcwd(buf, 512));  // ICI on met le nouveau chemin dans pwd
	if (find_value("PWD=", call->env, 1) || find_value("PWD=", call->env, 2)) //on verifie presence dans var env et dans var exportet si presence on modifie
		add_env(call, "PWD=", g_pwd, 1);
	if (find_value("OLDPWD=", call->env, 1) || find_value("OLDPWD=", call->env, 2))
		add_env(call, "OLDPWD=", g_oldpwd, 1);
}

int				ft_cd(char **func, t_call *call)
{
	int			i;
	char 		*dir; //ICI

	i = 0;
	if (func[1] && chdir(func[1]) == -1)
	{
		ft_printf_e("bash: line 1: cd: %s: %s\n", func[1], strerror(errno));  // JUSTE POUR LES TESTS
	//	ft_printf_e("minishell: cd: %s: %s\n", func[1], strerror(errno));
		return (EXIT_FAILURE);
	}
	else if (!func[1])
	{
		if (call->env)
		{
			dir = find_user(NULL, call->env);
			if (chdir(dir) == -1)
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

int check_sign(char *func, int *j, int *neg)
{
	int sign;

	sign = 0;
	while (func[*j] == '+')
	{
		sign++;
		if (sign > 1)
			return (0);
		(*j)++;
	}
	while (func[*j] == '-')
	{
		sign++;
		*neg = 1;
		if (sign > 1)
			return (0);
		(*j)++;
	}
	while (func[*j] == '+')
	{
		sign++;
		if (sign > 1)
			return (0);
		(*j)++;
	}
	return (1);
}

int check_numeric_argument(char *func, int *neg)
{
	int j;

	j = 0;
	while (func[j] == ' ')
		j++;
	if(!(check_sign(func, &j, neg)))
		return (0);
	while (func[j])
	{
		if (!ft_isdigit((int)func[j]))
			return (0);
		j++;
	}
	return (1);
}

int			check_sec_round_arg(char *func, int arg, int neg)
{
	unsigned long long res;
	unsigned long long max;
	
	max = 9223372036854775807;
	if (arg > 2)
	{
		ft_printf_e("bash: line 1: exit: too many arguments\n");
		exit_status = 1;
		exit_nb = exit_status;
		return (EXIT_FAILURE);
	}
	res = ft_atoll(func);
	if (res > (max + 1))
	{
		ft_printf_e("bash: line 1: exit: %s: numeric argument required\n", func);
		exit_nb = 255;
	}
	else
	{
		if (neg == 0)
			exit_nb = res % 256;
		else
			exit_nb = -(res % 256) + 256;
	}
	return (EXIT_SUCCESS);
}

void numeric_error(char *func)
{
	ft_printf_e("bash: line 1: exit: %s: numeric argument required\n", func); // message d'erreur du test mais pas dans mon bash....
	exit_nb = 255;
}

int				ft_builtin_exit(char **func, int *exit_info)
{
	int i;
	int arg;
	int neg;
	
	i = -1;
	arg = 0;
	neg = 0;
	while (func[++i])
		arg++;
	if (g_ret != 2)
		ft_printf("exit\n");   
	if (arg >= 2)
	{
		if (check_numeric_argument(func[1], &neg))
		{	
			if (check_sec_round_arg(func[1], arg, neg))
			{
			//	printf("nb : %d\n", exit_nb);fflush(stdout);
				return (EXIT_FAILURE);
			}
		}
		else
			numeric_error(func[1]);
	}
	i = -1;
	if (g_pids)
		while (g_pids[++i])
			kill(g_pids[i], 2);
	*exit_info = 1;
	
	return (exit_nb);
}
