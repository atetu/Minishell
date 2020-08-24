/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env_add.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atetu <atetu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/24 17:56:25 by atetu             #+#    #+#             */
/*   Updated: 2020/08/24 17:56:27 by atetu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int		replace_env_var(void **content, void *var, char *tmp)
{
	free(*content);
	*content = (void *)var;
	free(tmp);
	return (1);
}

void			add_env2(t_call *call, char *key, char *value)
{
	char		*var;
	t_list		*current;

	current = *call->env;
	if (find_value(key, call->env, 1))
	{
		var = ft_strjoin(find_value(key, call->env, 1), value);
		while (current)
		{
			if (!ft_strncmp(key, (char *)current->content, ft_strlen(key)))
			{
				free(current->content);
				current->content = (void *)var;
				break ;
			}
			current = current->next;
		}
	}
	else
	{
		var = ft_strjoin(key, value);
		ft_lstadd_back(call->env, ft_lstnew(var));
	}
	free(key);
}

int				add_env(t_call *call, char *key, char *value, int option)
{
	char		*var;
	t_list		*current;
	char		*tmp;

	var = ft_strjoin(key, value);
	current = *call->env;
	if (option == 0)
		ft_lstadd_back(call->env, ft_lstnew(var));
	else
	{
		while (current)
		{
			tmp = ft_substr(key, 0, ft_strlen(key) - 1);
			if ((!ft_strncmp(key, (char *)current->content, ft_strlen(key))) ||
			(!ft_strncmp(tmp, (char *)current->content, ft_strlen(tmp)) &&
			((char *)current->content)[ft_strlen(tmp)] == '\0'))
				if (replace_env_var(&current->content, (void *)var, tmp))
					break ;
			current = current->next;
			free(tmp);
		}
	}
	if (current)
		return (EXIT_SUCCESS);
	return (EXIT_FAILURE);
}
