/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_var.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atetu <atetu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/25 15:12:10 by thgermai          #+#    #+#             */
/*   Updated: 2020/08/13 12:32:57 by atetu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static char		*get_name_var(char *str)
{
	int			i;

	i = 1;
	if (str[0] != '$')
		return (NULL);
	while (str[i] && str[i] != ' ' && str[i] != '|'
		&& str[i] != ';' && str[i] != '\'' && str[i] != '"' && str[i] != '=')
		i++;
	return (ft_substr(str, 1, i - 1));
}

static int		get_n_var(char *str)
{
	int			i;
	int			in_quote;
	int			count;

	count = 0;
	in_quote = 0;
	i = -1;
	while (str[++i])
	{
		if (str[i] == '$' && !is_valide(str, i, 0) && (i == 0 ||   //ici
		(i > 0 && !is_backslash(str, i - 1))))	//ici
			count++;
	}
	return (count);
}

static char		*replace_var(char *str, int index, t_list **env, int option)
{
	char		*temp;
	char		*var;
	char		*var_name;
	int			i;

	temp = ft_substr(str, 0, index);
	if (!option)
	{
		var_name = get_name_var(str + index);
		var = find_value(var_name, env, 1);
		if (var)
			temp = ft_strjoin_f1(temp, var + ft_strlen(var_name) + 1);
		free(var_name);
	}
	if (option)
		temp = ft_strjoin_f12(temp, ft_itoa(exit_status));
	i = index;
	if (str[i + 1] && !(ft_isalpha(str[i + 1])) && str[i + 1] != '_' && str[i + 1] != '=')   //ICI
		i = i + 2;														//ICI
	else																//ICI
		while (str[i] && str[i] != '"' && str[i] != '\'' &&
			str[i] != ' ' && str[i] != '|' && str[i] != ';' && str[i] != '=')
			i++;
	temp = ft_strjoin_f1(temp, str + i);
	free(str);
	return (temp);
}

static char		*replace_old_pwd(char *str, int index, int opt)  //ICI   opt 1 pwd ; opt 2 oldpwd
{
	char		*temp;

	//printf("pwd: %s\n", g_pwd);fflush(stdout);
	temp = ft_substr(str, 0, index);
	if (opt == 1 && g_pwd)
		temp = ft_strjoin_f1(temp, g_pwd);
	if (opt == 2 && g_oldpwd)
		temp = ft_strjoin_f1(temp, g_oldpwd);
	return (temp);
}

char			*parse_var(char *str, char *func, t_list **env)   //ICI
{
	int			i;
	int			n;

	n = get_n_var(str);
	i = -1;
	while (n > 0 && str[++i])
	{
		if (str[i] == '$' && !is_valide(str, i, 0) && (i == 0 ||
		(i > 0 && !is_backslash(str, i - 1))) && (str[i + 1] && str[i + 1] != ' ')) //ICI
		{
			if (str[i + 1] && str[i + 1] == '=')
				;
			else if (str[i + 1] && str[i + 1] == '?')
				str = replace_var(str, i, env, 1);
			else if (!(ft_strncmp(func, "echo", 5)) && !(ft_strncmp(&str[i],
			"$PWD", 5)) && (!(str[i + 4]) || str[1 + 4] == ' '))  // ICI 
				str = replace_old_pwd(str, i, 1);  //ICI
			else if (!(ft_strncmp(func, "echo", 5)) && !(ft_strncmp(&str[i],
			"$OLDPWD", 8)) && (!(str[i + 7]) || str[1 + 7] == ' '))  // ICI 
				str = replace_old_pwd(str, i, 2);  //ICI
			else
				str = replace_var(str, i, env, 0);
			n--;
		}
	}
	return (str);
}
