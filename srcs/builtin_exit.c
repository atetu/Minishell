/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alicetetu <atetu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/15 11:31:57 by alicetetu         #+#    #+#             */
/*   Updated: 2020/08/15 11:32:00 by alicetetu        ###   ########.fr       */
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
	if(!(check_sign(func, &j, neg, &sign)))
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

static void		numeric_error(char *func)
{
	ft_printf_e("bash: line 1: exit: %s: numeric argument required\n", func); // message d'erreur du test mais pas dans mon bash....
	exit_nb = 255;
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
	//ft_printf("exit\n");    // A SUPPRIMER POUR LE TESTEUR UNQUEMENT
	if (arg >= 2)
	{
		if ((ret = check_numeric_argument(func[1], &neg)) != 0)
			if (check_sec_round_arg(func[1], arg, neg))
				return (EXIT_FAILURE);
		if (ret == 0)
			numeric_error(func[1]);
	}
	i = -1;
	if (g_pids)
		while (g_pids[++i])
			kill(g_pids[i], 2);
	*exit_info = 1;
	return (exit_nb);
}
