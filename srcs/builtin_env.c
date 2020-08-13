/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atetu <atetu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/30 17:24:16 by thgermai          #+#    #+#             */
/*   Updated: 2020/08/13 15:34:30 by atetu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void 			unset_env_var(char *key)
{
	if (!(ft_strncmp(key, "PWD=", 5)))   //ICI
		{
			free(g_pwd); // ICI
			g_pwd = ft_strdup(""); //ICI
		}
		if (!(ft_strncmp(key, "OLDPWD=", 8)))   //ICI
		{
			free(g_oldpwd); // ICI
			g_oldpwd = ft_strdup(""); //ICI
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
		j = -1;     //ICI
		while (func[i][++j])  //ICI  
		{					// ICI
			if (!(ft_isalnum((int)func[i][j])) && func[i][j] != '_') // ICI
			{
				ft_printf_e("minishell: unset: '%s': not a valid identifier\n", func[i]);  //ICI
				exit_nb = 1;   /// ATTENTION A METTRE PARTOUT OU ERREUR
				return (EXIT_FAILURE);
			}
		}
		key = ft_strjoin(func[i], "=");
		unset_env_var(key);
		if (find_value(key, call->env, 1))   // on cherche a la fois dans var env et dans var export
			delete_element(call, key);
		if (find_value(key, call->env, 2))
			delete_element(call, func[i]);
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

int				ft_env1(t_call *call)
{
	t_list		*current;
	t_list		**sorted_list;
	char		*key;

	sorted_list = sort_var_env(call->env);
	current = *sorted_list;
	while (current)
	{
		write(1, "declare -x ", 11);
		key = get_key((char *)current->content);
		write(1, key, ft_strlen(key) - 1);   //enleve le -1
	//	if (ft_strlen(find_value(key, sorted_list) + ft_strlen(key)))
		if (ft_strchr((char *)current->content, '='))  // ATTENTION PAR RAPPOT A VERSION THOMAS
			ft_printf("=\"%s\"\n", find_value(key, call->env, 1) + ft_strlen(key));   //enleve le =
		else
			write(1, "\n", 1);
		free(key);
		current = current->next;
	}
	ft_lstclear(sorted_list, &free);
	free(sorted_list);
	return (EXIT_SUCCESS);
}

int				check_export_errors(char *func)
{
	int j;
	
	if (func[0] == '=')
		{
			ft_printf_e("minishell: export: '%s': not a valid identifier\n", func);
			return (EXIT_FAILURE);
		}
		j = 0;
		while (func[j] && func[j] != '=')
		{
			if (!(ft_isalnum((int)func[j])) && func[j] != '_')
			{
				exit_nb = 1;
				ft_printf_e("minishell: export: '%s': not a valid identifier\n", func);
				return (EXIT_FAILURE);
			}
			j++;
		}
		return (EXIT_SUCCESS);
}

int				ft_export(t_call *call, char **func) // reste a verifier si les key n'est que alphanum
{
	int			i;
	char		*key;

	i = 0;
	if (func[1] == NULL)
		ft_env1(call);
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
			free(key);
		}
	}
	return (EXIT_SUCCESS);
}