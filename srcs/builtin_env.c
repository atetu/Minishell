/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/30 17:24:16 by thgermai          #+#    #+#             */
/*   Updated: 2020/08/28 14:42:26 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int				ft_env(t_call *call, char **func)
{
	t_list		*current;
	char		*key;

	if (func[1])
		return (EXIT_FAILURE);
	if (call->env)
	{
		current = *call->env;
		while (current)
		{
			key = get_key((char *)current->content);
			if (((char *)current->content)[ft_strlen(key) - 1] == '=')
			{
				write(1, (char *)current->content,
					ft_strlen((char*)current->content));
				write(1, "\n", 1);
			}
			free(key);
			current = current->next;
		}
	}
	return (EXIT_SUCCESS);
}

static void		write_env1(char *key, t_call *call, t_list *current)
{
	char		*to_print;

	to_print = NULL;
	write(1, "declare -x ", 11);
	write(1, key, ft_strlen(key) - 1);
	if (ft_strchr((char *)current->content, '='))
	{
		to_print = find_value(key, call->env, 1) + ft_strlen(key);
		ft_printf("=\"%s\"\n", to_print);
	}
	else
		write(1, "\n", 1);
	free(key);
}

int				ft_env1(t_call *call)
{
	t_list		*current;
	t_list		**sorted_list;
	char		*key;

	sorted_list = sort_var_env(call->env);
	current = *sorted_list;
	while (current)
	{
		key = get_key((char *)current->content);
		if (!ft_strncmp(key, "_=", 3))
			free(key);
		else
			write_env1(key, call, current);
		current = current->next;
	}
	ft_lstclear(sorted_list, &free);
	free(sorted_list);
	return (EXIT_SUCCESS);
}
