/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thgermai <thgermai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/16 10:44:15 by thgermai          #+#    #+#             */
/*   Updated: 2020/08/31 15:46:15 by thgermai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int		check_input(void)
{
	struct stat		buff;

	g_file = 0;
	fstat(STDIN_FILENO, &buff);
	if (S_ISREG(buff.st_mode))
		return (0);
	return (1);
}

static void		handle_file(char **env)
{
	char		*args;
	t_list		**list;
	int			go_on;

	go_on = 2;
	g_file = 1;
	list = tab_to_list(env);
	set_g_home(list);
	args = NULL;
	while (get_input(&args, &go_on, 2))
	{
		g_pids = NULL;
		if (ft_strlen(args))
			if (parse_args(args, list) == -1)
				break ;
		free(args);
	}
	if (args)
	{
		g_pids = NULL;
		if (ft_strlen(args))
			parse_args(args, list);
	}
	clear_all(args, list);
	exit(g_exit_nb);
}

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
	if (check_input())
		prompt(env);
	else
		handle_file(env);
	return (0);
}
