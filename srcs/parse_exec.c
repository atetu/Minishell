/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/02 22:45:09 by thgermai          #+#    #+#             */
/*   Updated: 2020/08/28 14:52:35 by user42           ###   ########.fr       */
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

static int		is_dir(char *bin)
{
	if (ft_strlen(bin) == 1 && bin[0] == '.')
	{
		ft_printf("bash: .: filename argument required .:\n");
		ft_printf("usage: . filename [arguments]\n");
		g_exit_status = 2;
		g_exit_nb = g_exit_status;
		return (-1);
	}
	else if (!ft_strncmp(bin, "/", 1) || !ft_strncmp(bin, "./", 2))
		return (1);
	return (0);
}

static int		set_exec(char **var, char **bin, char ***paths, t_call *call)
{
	int ret;

	if ((ret = is_dir(*bin)) == -1)
		return (-1);
	*var = find_value("PATH=", call->env, 1);
	if ((*bin)[0] && (*bin)[1] && (*bin)[0] == '.' && (*bin)[1] == '/')
		*bin = fill_pwd(*bin);
	if (*var == NULL)
		*paths = NULL;
	else
		*paths = ft_split(*var, ':');
	return (ret);
}

char			*parse_exec(t_call *call, char *bin)
{
	char		**paths;
	char		*bin_cpy;
	char		*path;
	char		*var;
	int			ret;

	path = NULL;
	bin_cpy = ft_strdup(bin);
	if ((ret = set_exec(&var, &bin, &paths, call)) == -1)
		return (NULL);
	if (!(check_double_points(bin)))
		return (NULL);
	else if (!(path = find_path(paths, bin, bin_cpy)))
	{
		handle_error(ret, var, bin_cpy);
		g_exit_status = 127;
		g_exit_nb = g_exit_status;
		clean_exec(&paths, &bin, &bin_cpy);
		return (NULL);
	}
	if (!(check_existing_path(&path, &paths, &bin, &bin_cpy)))
		return (NULL);
	clean_exec(&paths, &bin, &bin_cpy);
	return (path);
}
