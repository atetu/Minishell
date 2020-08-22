/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thgermai <thgermai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/02 22:27:19 by thgermai          #+#    #+#             */
/*   Updated: 2020/08/22 16:52:10 by thgermai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void			wait_pids(pid_t *pids, int size, t_call *calls)
{
	int			i;
	int			status;

	i = -1;
	(void)calls;
	while (++i < size && pids[i] != -1)
	{
	//	printf("la\n");fflush(stdout);
		waitpid(pids[i], &status, 0);
	//	printf("coucou\n");fflush(stdout);
		if (WIFEXITED(status))
		{
	//		printf("ici\n");fflush(stdout);
			g_exit_status = WEXITSTATUS(status);
			g_exit_nb = g_exit_status;
		}
	}
}

static void		manage_pipes(t_call *calls, int pipes[][2], char *str, int *exit_info)
{
	int i;
	//int n_pipes;  a ajouter pour VM

	create_pipes(calls, pipes);    // n_pipes = ....
	i = -1;
	while (calls[++i].str)
		connect_pipes(calls, pipes);   // 3e arg: n_pipes
	i = -1;
	while (calls[++i].str)
		g_pids[i] = exec1(&calls[i], pipes, get_n_pipes(str, 0), exit_info);
	close_pipes(pipes, get_n_pipes(str, 0));
	wait_pids(g_pids, get_n_pipes(str, 0) + 1, calls);
}

static int		exec_input(char *str, t_list **env)
{
	t_call		calls[get_n_pipes(str, 0) + 2];
	int			pipes[get_n_pipes(str, 0)][2];
	int			i;
	int			exit_info;

	i = -1;
	exit_info = 0;
	if (!(g_pids = malloc(sizeof(pid_t) * (get_n_pipes(str, 0) + 2))))
	{
		ft_printf_e("Minishell: error: malloc failed\n");
		return (-1);
	}
	g_pids[get_n_pipes(str, 0) + 1] = 0;
	parse_pipes(str, calls);
	while (calls[++i].str)
		parse_call(&calls[i], env);
	if (i > 1)
		manage_pipes(calls, pipes, str, &exit_info);
	else
		exec2(&calls[0], &exit_info);
	clean_calls(calls);
	free(g_pids);
	if (exit_info == 1)
		return (-1);
	return (0);
}

//Nouvelle fonction
static int		parse_args(char *args, t_list **list)
{
	char	**split_args;
	int		i;
	int		ret;

	split_args = NULL;
	i = -1;
	ret = 0;
	if (ft_strlen(args))
	{
		split_args = parse_semicolon(args);
		if (split_args)
			while (split_args[++i])
				if ((ret = exec_input(split_args[i], list)) == -1)
					break ;
	}
	clean_array(split_args);
	return (ret);
}

void set_g_home(t_list **list)
{
	char		*value;

	value = find_value("HOME=", list, 1); // ICI
	if (value)   //ICI
		g_home = ft_strdup(value + 5); //ICI
	else
		g_home = ft_strdup("");
}

void			prompt(char **env)
{
	char		*args;
	t_list		**list;
	char 		**split_args;
	int			go_on;

	go_on = 0;
	list = tab_to_list(env);
	set_g_home(list);
	//g_home = ft_strdup(find_value("HOME=", list, 1) + 5); // ICI
	args = NULL;
	split_args = NULL;
	while (1)
	{
		g_pids = NULL;
		print();
		if (!(get_next_line(0, &args, &go_on)))
			if (control_d())
				break;
		if (ft_strlen(args))
			if (parse_args(args, list) == -1)
				break ;
		free(args);
	}
	clear_all(args, list);
	exit(g_exit_nb);
}
