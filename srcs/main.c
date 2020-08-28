/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/16 10:44:15 by thgermai          #+#    #+#             */
/*   Updated: 2020/08/28 14:47:47 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int				main(int ac, char **av, char **env)
{
	char buf[512];

	(void)ac;
	(void)av;
	g_pids = NULL;
	g_exit_nb = 0;
	if (signal(SIGINT, &control_c) == SIG_ERR)
	{
		ft_printf_e("Could not set signal handler\n");
		return (EXIT_FAILURE);
	}
	if (signal(SIGQUIT, &control_quit) == SIG_ERR)
	{
		ft_printf_e("Could not set signal handler\n");
		return (EXIT_FAILURE);
	}
	g_pwd = ft_strdup(getcwd(buf, 512));
	g_oldpwd = ft_strdup("");
	g_last = ft_strjoin(get_cwd(), "/minishell");
	prompt(env);
	return (0);
}
