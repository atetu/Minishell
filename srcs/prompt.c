/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atetu <atetu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/02 22:27:19 by thgermai          #+#    #+#             */
/*   Updated: 2020/08/24 17:37:54 by atetu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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

static void		set_g_home(t_list **list)
{
	char		*value;

	value = find_value("HOME=", list, 1);
	if (value)
		g_home = ft_strdup(value + 5);
	else
		g_home = ft_strdup("");
}

void			print(void)
{
	//ft_printf("\033[1;32mMINISHELL \033[0m 👉 ");
}

void			prompt(char **env)
{
	char		*args;
	t_list		**list;
	char		**split_args;
	int			go_on;

	go_on = 0;
	list = tab_to_list(env);
	set_g_home(list);
	args = NULL;
	split_args = NULL;
	while (1)
	{
		g_pids = NULL;
		print();
		if (!(get_next_line(0, &args, &go_on)))
			if (control_d())
				break ;
		if (ft_strlen(args))
			if (parse_args(args, list) == -1)
				break ;
		free(args);
	}
	clear_all(args, list);
	exit(g_exit_nb);
}
