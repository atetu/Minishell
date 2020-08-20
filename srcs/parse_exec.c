/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atetu <atetu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/02 22:45:09 by thgermai          #+#    #+#             */
/*   Updated: 2020/08/20 13:15:18 by atetu            ###   ########.fr       */
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
//	free(bin);   //ici
	return (temp);
}

static char		*find_path(char **paths, char *bin, char *old_bin)
{
	char			*path;
	int				i;
	struct stat		stats;
	DIR				*rep;

	if ((rep = opendir(bin)) != NULL)  //ICI ./minishell_tester
	{
		closedir(rep);
		ft_printf_e("bash: line 1: %s: is a directory\n", old_bin);
		return (NULL);
	}
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
		//if ((rep = opendir(path)) != NULL)  //ICI ./minishell_tester
	//	{
	//		printf("icicic\n");fflush(stdout);
	//		closedir(rep);
	//		ft_printf_e("bash: line 1: %s: is a directory\n", bin);
	//	}
		free(path);
	}
	}
	ft_printf_e("bash: line 1: %s: No such file or directory\n", old_bin); //ici
	return (NULL);
}

char			*parse_exec(t_call *call, char *bin)
{
	char		**paths;
	char		*path;
	char		*var;
	int			i;
	char		*bin_filled; //ici
	
	i = -1;
	bin_filled = NULL;
	//printf("bin: %s", bin);fflush(stdout);
	var = find_value("PATH=", call->env, 1);  // ICI
/*	if (!var)
	{
		ft_printf_e("Minishell: path variable doesn't exist\n");
		exit(3); /// ATTENTION AU EXIT
	}*/
	if (bin[0] && bin[1] && bin[0] == '.' && bin[1] == '/')
		bin_filled = fill_pwd(bin); //ici
	else
		bin_filled = ft_strdup(bin);	
	if (var == NULL)    //ICI
		paths = NULL;	//ICI
	else
		paths = ft_split(var, ':');   // modifie var en var_path
	if (!(path = find_path(paths, bin_filled, bin)))
	{	
		//printf("icicic\n");fflush(stdout);
//		if (!var)
	//	{	
		//exit
	//	ft_printf_e("bash: line 1: %s: No such file or directory\n", bin);    //JUSTE POUR LES TESTS!!!
			//	ft_printf_e("minishell: %s: No such file or directory\n", bin);   //ici
//		}
//		else
//		{	
			//	ft_printf_e("Minishell: %s: command not found\n", bin);// JUSTE POUR LES TESTS1    JE CROIS QU'ON N'A PAS BESOIN DE CE MESSAGE
//			ft_printf_e("bash: line 1: %s: command not found\n", bin);// JUSTE POUR LES TESTS1
//		}
	}
	i = -1;
	clean_array(paths);
	free(bin);
	free(bin_filled);
	return (path);
}
