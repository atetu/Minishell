/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thgermai <thgermai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/16 10:44:15 by thgermai          #+#    #+#             */
/*   Updated: 2020/08/19 14:34:48 by thgermai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int				main(int ac, char **av, char **env)
{
	char buf[512];  //ICI

	(void)ac;
	(void)av;
	g_pids = NULL;
	g_exit_nb = 0;
	if (signal(SIGINT, control_c) == SIG_ERR)
	{
		ft_printf_e("%s\n", "Could not set signal handler");
		return (EXIT_FAILURE);
	}
	if (signal(SIGQUIT, control_quit) == SIG_ERR)
	{
		ft_printf_e("%s\n", "Could not set signal handler");
		return (EXIT_FAILURE);
	}
	g_pwd = ft_strdup(getcwd(buf, 512));  // a free
	g_oldpwd = ft_strdup("");  //a free
	g_last = ft_strjoin(get_cwd(), "/minishell");
	prompt(env);
	return (0);
}
