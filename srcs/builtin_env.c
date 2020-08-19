/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atetu <atetu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/30 17:24:16 by thgermai          #+#    #+#             */
/*   Updated: 2020/08/19 11:53:44 by atetu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void 			unset_env_var(char *key)
{
	if (!(ft_strncmp(key, "PWD=", 5)))
	{
		free(g_pwd);
		g_pwd = ft_strdup("");
	}
	if (!(ft_strncmp(key, "OLDPWD=", 8)))
	{
		free(g_oldpwd);
		g_oldpwd = ft_strdup("");
	}
}

int				ft_unset(t_call *call, char **func)
{
	int			i;
	char		*key;
	int			j;

	i = 0;
	while (func[++i])
	{
		j = -1;
		while (func[i][++j])
		{
			if (!ft_isalnum((int)func[i][j]) && func[i][j] != '_')
			{
				// ft_printf_e("Minishell: unset: '%s': not a valid identifier\n", func[i]);
				ft_printf_e("bash: line 1: unset: `%c': not a valid identifier\n", func[i][j]);
				return ((g_exit_nb = EXIT_FAILURE));
			}
		}
		key = ft_strjoin(func[i], "=");
		unset_env_var(key);
		if (ft_strncmp(key, "_=", 3))
		{
			if (find_value(key, call->env, 1))   // on cherche a la fois dans var env et dans var export
				delete_element(call, key);
			if (find_value(key, call->env, 2))
				delete_element(call, func[i]);
		}
		free(key);
	}
	return (EXIT_SUCCESS);
}

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

int				ft_env1(t_call *call, char **func)
{
	t_list		*current;
	t_list		**sorted_list;
	char		*key;
	int			i;

	i = -1;
	sorted_list = sort_var_env(call->env);
	current = *sorted_list;
	while (current)
	{
		if (ft_strncmp(current->content, "_=", 2) || (!(ft_strncmp(current->content, "_=", 2)) && g_last == NULL)) // ici
		{
		write(1, "declare -x ", 11);
		key = get_key((char *)current->content);
		write(1, key, ft_strlen(key) - 1);
		if (ft_strchr((char *)current->content, '='))
			ft_printf("=\"%s\"\n", find_value(key, call->env, 1) + ft_strlen(key));
		else
			write(1, "\n", 1);
		free(key);
		}
		current = current->next;
	}
	ft_lstclear(sorted_list, &free);
	free(sorted_list);
	while (func[++i])// ICI
		;
	g_last = ft_strdup(func[i -1]);  //ICI
	return (EXIT_SUCCESS);
}

int				check_export_errors(char *func)
{
	int i;

	if (func[0] == '=')
	{
		// ft_printf_e("minishell: export: '%s': not a valid identifier\n", func);
		ft_printf_e("bash: line 1: export: `%c': not a valid identifier\n", func[0]);
		return (EXIT_FAILURE);
	}
	i = 0;
	while (func[i] && func[i] != '=')
	{
		if (!ft_isalnum((int)func[i]) && func[i] != '_')
		{
			// ft_printf_e("minishell: export: '%s': not a valid identifier\n", func);
			ft_printf_e("bash: line 1: export: `%c': not a valid identifier\n", func[i]);
			return ((g_exit_nb = EXIT_FAILURE));
		}
		i++;
	}
	return (EXIT_SUCCESS);
}

int				ft_export(t_call *call, char **func) // reste a verifier si les key n'est que alphanum
{
	int			i;
	char		*key;
	char *tmp;

	i = -1; //ici
	if (func[1] == NULL)
		ft_env1(call, func);
	while (func[++i]) // ici
		;
	if (g_last) // ici
		free(g_last);//ici
	g_last = ft_strdup(func[i]); // ici
	i = 0;
	while (func[++i])
	{
		if (check_export_errors(func[i]))
			return (EXIT_FAILURE);
		if (func[i][0] != '=')
		{
			key = get_key(func[i]);
			if (find_value(key, call->env, 1))
			{
				if (ft_strchr(func[i], '='))
					add_env(call, key, ft_strchr(func[i], '=') + 1, 1);
			}
			else if (ft_strchr(func[i], '='))
				add_env(call, key, ft_strchr(func[i], '=') + 1, 0);
			else
				add_env(call, func[i], "\0", 0);
			tmp = ft_substr(key, 0, ft_strlen(key) -1); // ICI
			add_env(call, "_=", ft_strjoin("_=", tmp), 1); // ICI
			free(tmp);
			free(key);
		}
	}
	return (EXIT_SUCCESS);
}
