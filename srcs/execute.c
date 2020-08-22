/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thgermai <thgermai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/02 22:47:56 by thgermai          #+#    #+#             */
/*   Updated: 2020/08/22 15:50:15 by thgermai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void		refresh_var_underscore(char **func, t_call *call)
{
	int			i;

	i = -1;
	while(func[++i])
		;
	if (!(!ft_strncmp(func[0], "export", ft_strlen(func[0])) && !func[1]))
	{
		if (find_value("_=", call->env, 1))
			add_env(call, "_=", func[i - 1], 1);
		else
			add_env(call, "_=", func[i - 1], 0);
	}
}

pid_t			exec1(t_call *call, int pipes[][2], int size, int *exit_info)
{
	char		**func;
	pid_t		pid;
	char		**env_var;

	if (call->in == -1)
	{
		g_exit_status = 1;  //ICI
		g_exit_nb = 1;  //ICI
		return (-1);
	}
	if (!(func = parse(call->str, call->env)))
		return (-1);
	refresh_var_underscore(func, call);
	if (!known_func(func[0]))
	{
		if (!(func[0] = parse_exec(call, func[0])))
		{
			clean_array(func);
			return (-1);
		}
	}
	env_var = list_to_tab(call->env);
	if ((pid = fork()) == 0)
	{
		duplicate_fd(call);
		close_pipes(pipes, size);
		exit(execute(call, func, env_var, exit_info));
	}
	clean_array(func);
	free(env_var);
	if (*exit_info == 1)
		return (-1);
	return (pid);
}

void			exec2(t_call *call, int *exit_info)
{
	char		**func;
	char		**var_env;
	pid_t		pid;

	if (call->in == -1)
	{
		g_exit_status = 1;  // <error ; echo $?
		g_exit_nb = 1;
		return ;
	}
	if (!(func = parse(call->str, call->env)))
		return ;
	refresh_var_underscore(func, call);
	var_env = list_to_tab(call->env);
	if (known_func(func[0]))
	{
		exec_knonw(call, func, var_env, exit_info);
		return ;
	}
	if (!(func[0] = parse_exec(call, func[0]))) // pourquoi pas dans exec 1? chose a free ????
	{
		free(var_env);
		for (int i = 1; func[i]; i++)
			free(func[i]);
		free(func);
		return ;
	}
	if ((pid = fork()) == 0)
	{
		duplicate_fd(call);
		execve(func[0], func, var_env);
	//	ft_printf_e("Minishell: execve: %s\n", strerror(errno));
		exit(EXIT_FAILURE);
	}
	clean_array(func);
	free(var_env);
	if (*exit_info)
		return ;
	wait_pids(&pid, 1, call);
}
