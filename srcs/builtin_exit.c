/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/15 11:31:57 by alicetetu         #+#    #+#             */
/*   Updated: 2020/09/09 11:01:29 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int		check_sign(char *func, int *j, int *neg, int *sign)
{
	while (func[*j] == '+')
	{
		(*sign)++;
		if (*sign > 1)
			return (0);
		(*j)++;
	}
	while (func[*j] == '-')
	{
		(*sign)++;
		*neg = 1;
		if (*sign > 1)
			return (0);
		(*j)++;
	}
	while (func[*j] == '+')
	{
		(*sign)++;
		if ((*sign) > 1)
			return (0);
		(*j)++;
	}
	return (1);
}

static int		check_numeric_argument(char *func, int *neg)
{
	int j;
	int sign;

	sign = 0;
	j = 0;
	while (func[j] == ' ')
		j++;
	if (!(check_sign(func, &j, neg, &sign)))
		return (0);
	while (func[j])
	{
		if (!ft_isdigit((int)func[j]))
			return (0);
		j++;
	}
	return (1);
}

static int		check_sec_round_arg(char *func, int arg, int neg)
{
	unsigned long long res;
	unsigned long long max;

	max = 9223372036854775807;
	if (arg > 2)
	{
		ft_printf_e("minishell: exit: too many arguments\n");
		g_exit_status = 1;
		g_exit_nb = g_exit_status;
		return (EXIT_FAILURE);
	}
	res = ft_atoll(func);
	if (res > (max + 1))
	{
		ft_printf_e("minishell: exit: %s: numeric argument required\n", func);
		g_exit_nb = 2;
	}
	else
	{
		if (neg == 0)
			g_exit_nb = res % 256;
		else
			g_exit_nb = -(res % 256) + 256;
	}
	return (EXIT_SUCCESS);
}

static void		print_exit(char *str, int opt)
{
	if (opt == 1)
	{
		if (!g_file)
			ft_printf("%s\n", str);
	}
	else if (opt == 2)
	{
		ft_printf_e("minishell: exit: %s: numeric argument required\n", str);
		g_exit_nb = 2;
	}
}

int				ft_builtin_exit(char **func, int *exit_info)
{
	int i;
	int arg;
	int neg;
	int ret;

	i = -1;
	arg = 0;
	neg = 0;
	while (func[++i])
		arg++;
	print_exit("exit", 1);
	if (arg >= 2)
	{
		if ((ret = check_numeric_argument(func[1], &neg)) != 0)
			if (check_sec_round_arg(func[1], arg, neg))
				return (EXIT_FAILURE);
		if (ret == 0)
			print_exit(func[1], 2);
	}
	i = -1;
	if (g_pids)
		while (g_pids[++i])
			kill(g_pids[i], 2);
	*exit_info = 1;
	return (g_exit_nb);
}
