/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atetu <atetu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/02 22:47:56 by thgermai          #+#    #+#             */
/*   Updated: 2020/08/19 13:49:26 by atetu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

pid_t			exec1(t_call *call, int pipes[][2], int size, int *exit_info)
{
	char		**func;
	int			i;
	pid_t		pid;
	char		**env_var;
	int ret;

//	printf("ici");fflush(stdout);
	i = -1;
	env_var = list_to_tab(call->env);
	if (!(func = parse(call->str, call->env)))
		return (-1);
	if (!known_func(func[0]))
		if (!(func[0] = parse_exec(call, func[0])))
			return (-1);
	if ((pid = fork()) == 0)
	{
		duplicate_fd(call);
		close_pipes(pipes, size);
		//exit(execute(call, func, env_var, exit_info));
		ret = execute(call, func, env_var, exit_info);
		add_env(call, "_=", ft_strdup("/usr/bin/env"), 1); // icic
		exit(ret);
	}
	clean_array(func);
	free(env_var);
	add_env(call, "_=", ft_strdup("/usr/bin/env"), 1); // icic
	if (*exit_info == 1)
		return (-1);
	return (pid);
}

void			exec2(t_call *call, int *exit_info)
{
	char		**func;
	char		**var_env;
	pid_t		pid;

//	printf("la");fflush(stdout);
	if (!(func = parse(call->str, call->env)))
		return ;
	//printf("la");fflush(stdout);
	var_env = list_to_tab(call->env);
	if (known_func(func[0]))
	{
		exec_knonw(call, func, var_env, exit_info);
		add_env(call, "_=", ft_strdup("/usr/bin/env"), 1); //ici
		return ;
	}
	func[0] = parse_exec(call, func[0]);
	if ((pid = fork()) == 0)
	{
		duplicate_fd(call);
		execve(func[0], func, var_env);
	//	ft_printf_e("Minishell: execve: %s\n", strerror(errno));
		exit(EXIT_FAILURE);
	}
	clean_array(func);
	free(var_env);
	add_env(call, "_=", ft_strdup("/usr/bin/env"), 1); //ici
	if (*exit_info)
		return ;
	wait_pids(&pid, 1, call);
}
