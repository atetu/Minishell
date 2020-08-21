/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utiles.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thgermai <thgermai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/02 22:48:42 by thgermai          #+#    #+#             */
/*   Updated: 2020/08/17 14:49:18 by thgermai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void			exec_knonw(t_call *call, char **func, char **var_env,
int *exit_info) //ICI
{
	int			fds[2];

	fds[0] = dup(0);
	fds[1] = dup(1);
	duplicate_fd(call);
	g_exit_status = execute(call, func, var_env, exit_info); //ici
	g_exit_nb = g_exit_status;    // ICI pour exit
	clean_array(func);
	free(var_env);
	dup2(fds[0], 0);
	dup2(fds[1], 1);
	close(fds[0]);
	close(fds[1]);
}

void			duplicate_fd(t_call *call)
{
	if (call->in != 0)
	{
		dup2(call->in, 0);
		close(call->in);
	}
	if (call->out != 1)
	{
		dup2(call->out, 1);
		close(call->out);
	}
}

int				execute(t_call *call, char **func, char **env, int *exit_info)
{//ATTENTION J'AI CHANGE TOUS LES NOMBRES
	if (!ft_strncmp(func[0], "echo", 5))
		return (ft_echo(func));
	else if (!ft_strncmp(func[0], "cd", 3))
		return (ft_cd(func, call));
	else if (!ft_strncmp(func[0], "pwd", 4))
		return (ft_pwd());
	else if (!ft_strncmp(func[0], "export", 7))
		return (ft_export(call, func));
	else if (!ft_strncmp(func[0], "unset", 6))
		return (ft_unset(call, func));
	else if (!ft_strncmp(func[0], "env", 400))
		return (ft_env(call, func));         //ici
	else if (!ft_strncmp(func[0], "exit", 5))
		return (ft_builtin_exit(func, exit_info));  //ici
	else
	{
		execve(func[0], func, env);
	//	printf("herererere\n");fflush(stdout);
	//	ft_printf_e("Minishell: execve: %s\n", strerror(errno));
		return (EXIT_FAILURE);
	}
}
