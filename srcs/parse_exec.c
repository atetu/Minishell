/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thgermai <thgermai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/02 22:45:09 by thgermai          #+#    #+#             */
/*   Updated: 2020/08/22 15:34:35 by thgermai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static char		*fill_pwd(char *bin)
{
	char		*current_dir;
	char		*temp;
	char		*cwd;

	cwd = ft_strdup(get_cwd());
	current_dir = ft_strjoin(cwd, "/");
	temp = ft_strjoin(current_dir, bin + 2);
	free(current_dir);
	free(bin);
	free(cwd);
	return (temp);
}

static char		*check_is_file(char *bin, char *original_bin)
{
	struct stat		stats;

	ft_memset(&stats, 0, sizeof(stats));
	if (stat(bin, &stats) != -1)
	{
		if (S_ISDIR(stats.st_mode))
		{
			ft_printf_e("bash: %s: is a directory\n", original_bin);
			return (ft_strdup(""));
		}
		return (ft_strdup(bin));
	}
	return (NULL);
}

static char		*find_path(char **paths, char *bin, char *original_bin)
{
	char			*path;
	int				i;
	struct stat		stats;
	char			*temp;

	temp = check_is_file(bin, original_bin);
	if (temp)
		return (temp);
	i = -1;
	if (paths)
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

static void		clean_exec(char **paths[], char **bin, char **original_bin)
{
	clean_array(*paths);
	free(*bin);
	free(*original_bin);
}

static int		is_dir(char *bin)
{
	if (ft_strlen(bin) == 1 && bin[0] == '.')
	{
		ft_printf("bash: .: filename argument required .:\n"); // a modifier plus tard
		ft_printf("usage: . filename [arguments]\n");
		g_exit_status = 2;  //ICI
		g_exit_nb = g_exit_status; // ICI
		return (-1);
	}
	else if (!ft_strncmp(bin, "/", 1) || !ft_strncmp(bin, "./", 2))
		return (1);
	return (0);
}

int				set_exec(char **var, char **bin, char ***paths, t_call *call)  //ICI
{
	int ret;

	if ((ret = is_dir(*bin)) == -1)
		return (-1);
	*var = find_value("PATH=", call->env, 1); //ICI
	if ((*bin)[0] && (*bin)[1] && (*bin)[0] == '.' && (*bin)[1] == '/')
		*bin = fill_pwd(*bin);
	if (*var == NULL)
		*paths = NULL;
	else
		*paths = ft_split(*var, ':');
	return (ret);
}

int				check_double_points(char *original_bin) //ICI
{
	if (!ft_strncmp(original_bin, "..", 3))
	{
		ft_printf_e("bash: ..: command not found\n");
		g_exit_status = 127;   // ICI
		g_exit_nb = g_exit_status; // ICI
		return (0);
	}
	return (1);
}

int				check_existing_path(char **path, char ***paths, char **bin, char **original_bin) // ICI
{
	if (*path && !ft_strlen(*path))
	{
		free(*path);
		clean_exec(paths, bin, original_bin);
		return (0);
	}
	return (1);
}

char			*parse_exec(t_call *call, char *bin) // return null si probleme
{
	char		**paths;
	char		*original_bin;
	char		*path;
	char		*var;
	int			ret;

	path = NULL;
	original_bin = ft_strdup(bin);
	if ((ret = set_exec(&var, &bin, &paths, call)) == -1) //ICI norminette
		return (NULL);
	if (!(check_double_points(bin)))
		return (NULL);
	else if (!(path = find_path(paths, bin, original_bin)))
	{
		if (ret == 1 || !var)  // ICI  si PATH est unset, le message d'erreur ne sera jamais "commad not found"
			ft_printf_e("bash: line 1: %s: %s\n", original_bin, strerror(errno));
		else // ICI
			ft_printf_e("bash: line 1: %s: command not found\n", original_bin); //ICI
		g_exit_status = 127; // ICI
		g_exit_nb = g_exit_status; //ICI
		clean_exec(&paths, &bin, &original_bin);
		return (NULL);
	}
	if (!(check_existing_path(&path, &paths, &bin, &original_bin))) // ICI
		return (NULL); //ICI
	clean_exec(&paths, &bin, &original_bin);
	return (path);
}
