/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atetu <atetu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/02 22:45:09 by thgermai          #+#    #+#             */
/*   Updated: 2020/08/12 14:51:36 by atetu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static char		*fill_pwd(char *bin)
{
	char		*current_dir;
	char		*temp;

	current_dir = ft_strjoin(get_cwd(), "/");
	temp = ft_strjoin(current_dir, bin + 2);
	free(current_dir);
	free(bin);
	return (temp);
}

static char		*find_path(char **paths, char *bin)
{
	char			*path;
	int				i;
	struct stat		stats;

	if (stat(bin, &stats) != -1)
		return (ft_strdup(bin));
	i = -1;
	if (paths) // ICI
	{
	while (paths[++i])
	{
		if (i == 0)
			path = ft_strjoin(paths[i] + 5, "/");
		else
			path = ft_strjoin(paths[i], "/");
		path = ft_strjoin_f1(path, bin);
		if (stat(path, &stats) != -1)
			return (path);
		free(path);
	}
	}
	return (NULL);
}

char			*parse_exec(t_call *call, char *bin)
{
	char		**paths;
	char		*path;
	char		*var;
	int			i;

	i = -1;
	var = find_value("PATH=", call->env, 1);  // ICI
/*	if (!var)
	{
		ft_printf_e("Minishell: path variable doesn't exist\n");
		exit(3); /// ATTENTION AU EXIT
	}*/
	if (bin[0] && bin[1] && bin[0] == '.' && bin[1] == '/')
		bin = fill_pwd(bin);
	if (var == NULL)    //ICI
		paths = NULL;	//ICI
	else
		paths = ft_split(var, ':');   // modifie var en var_path
	if (!(path = find_path(paths, bin)))
	{	
		if (!var)
		{	
			ft_printf_e("bash: line 1: %s: No such file or directory\n", bin);    //JUSTE POUR LES TESTS!!!
			//	ft_printf_e("minishell: %s: No such file or directory\n", bin);   //ici
		}
		else
		{	
			//	ft_printf_e("Minishell: %s: command not found\n", bin);// JUSTE POUR LES TESTS1
			ft_printf_e("bash: line 1: %s: command not found\n", bin);// JUSTE POUR LES TESTS1
		}
	}
	i = -1;
	clean_array(paths);
	free(bin);
	return (path);
}
