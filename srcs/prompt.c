/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/02 22:27:19 by thgermai          #+#    #+#             */
/*   Updated: 2020/09/04 16:39:40 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int		exec_input(char *str, t_list **env)
{
	t_call		*calls;
	int 		**pipes;
	int			i;
	int			exit_info;
	int 		n_pipes;

	i = -1;
	exit_info = 0;
	if (!(calls = init_array(str)))
		return (-1);
	//ft_printf("1\n");
	pipes = NULL;
	n_pipes = get_n_pipes(str, 0);
//	ft_printf("2\n");
	if (!(init_pipes(n_pipes, &pipes)))
		return (-1);
//	ft_printf("3\n");
	g_pids[get_n_pipes(str, 0) + 1] = 0;
	if (parse_pipes(str, calls) == -1)
		return (0);
	while (calls[++i].str)
		parse_call(&calls[i], env);
	if (i > 1)
		manage_pipes(calls, pipes, str, &exit_info);
	
	else
		exec2(&calls[0], &exit_info);
	clean_calls(calls);
	clean_pipes(pipes, n_pipes);
	free(g_pids);
	if (exit_info == 1)
		return (-1);
	return (0);
}

int				parse_args(char *args, t_list **list)
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
	//	ft_printf("ici\n");
		if (split_args)
			while (split_args[++i])
			{
			//	ft_printf("entree\n");
				if ((ret = exec_input(split_args[i], list)) == -1)
					break ;
			//	ft_printf("sortie\n");
			}
	}
	clean_array(split_args);
	return (ret);
}

void			set_g_home(t_list **list)
{
	char		*value;

	value = find_value("HOME=", list, 1);
	if (value)
		g_home = ft_strdup(value + 5);
	else
		g_home = ft_strdup("");
}

void			prompt(char **env)
{
	char		*args;
	t_list		**list;
	int			go_on;

	go_on = 0;
	list = tab_to_list(env);
	set_g_home(list);
	args = NULL;
	while (1)
	{
		g_pids = NULL;
		print();
		if (!get_input(&args, &go_on, 1))
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
