/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atetu <atetu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/02 22:27:19 by thgermai          #+#    #+#             */
/*   Updated: 2020/08/13 18:49:54 by atetu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void			wait_pids(pid_t *pids, int size, t_call *calls)
{
	int			i;
	int			status;

	i = -1;
	(void)calls; // a delete
	while (++i < size && pids[i] != -1)
	{
		waitpid(pids[i], &status, 0);
		if (WIFEXITED(status))
			exit_status = WEXITSTATUS(status);
	}
}

static void		manage_pipes(t_call *calls, int pipes[][2], char *str, int *exit_info)
{
	int i;

	create_pipes(calls, pipes);
	i = -1;
	while (calls[++i].str)
		connect_pipes(calls, pipes);
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
	int			exit_info; //ICI
//	int			ret;   //ICI

	i = -1;
//	ret = 0;   //icic
	exit_info = 0; //ici
	if (!(g_pids = malloc(sizeof(pid_t) * (get_n_pipes(str, 0) + 2))))
	{
		ft_printf_e("Minishell: error: malloc failed\n");
		return (-1);
	}
	g_pids[get_n_pipes(str, 0) + 1] = 0;
	parse_pipes(str, calls);
	while (calls[++i].str)
		parse_call(&calls[i], env);
//	if (ret != -1)
//	{
	if (i > 1)
		manage_pipes(calls, pipes, str, &exit_info);
	else
		exec2(&calls[0], &exit_info);
//	}
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

void			clear_all(t_list **list)
{
	ft_lstclear(list, &free);
	free(g_pwd);
	free(g_oldpwd);
}

void			prompt(char **env)
{
	char		*args;
	t_list		**list;
	char 		**split_args;
//	int			i;
	int			go_on; //ici

	go_on = 0;   //ici
	exit_nb = 0;
	list = tab_to_list(env);
	args = NULL;
	split_args = NULL;
//	i = -1;
	while (1)
	{
		g_pids = NULL;
		print();
		if (get_next_line(0, &args, &go_on) == 0)
		{
			if (!(control_d()))
				exit(exit_status);
		}
		printf("args: %s\n", args);fflush(stdout);
		if (ft_strlen(args))
			if (parse_args(args, list) == -1)
				break ;
		free(args);
	}
//	ft_lstclear(list, &free);
	clear_all(list);  // pour norme nouvelle fonction
//	system("leaks minishell");
	ft_printf("exit\n");
	exit(exit_status);
}
