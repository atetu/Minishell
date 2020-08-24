/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_exec_utiles.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atetu <atetu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/24 17:36:27 by atetu             #+#    #+#             */
/*   Updated: 2020/08/24 17:37:01 by atetu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int		check_double_points(char *original_bin)
{
	if (!ft_strncmp(original_bin, "..", 3))
	{
		ft_printf_e("bash: ..: command not found\n");
		g_exit_status = 127;
		g_exit_nb = g_exit_status;
		return (0);
	}
	return (1);
}

int		check_existing_path(char **path, char ***paths,
	char **bin, char **original_bin)
{
	if (*path && !ft_strlen(*path))
	{
		free(*path);
		clean_exec(paths, bin, original_bin);
		return (0);
	}
	return (1);
}

char	*check_is_file(char *bin, char *original_bin)
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

void	clean_exec(char **paths[], char **bin, char **original_bin)
{
	clean_array(*paths);
	free(*bin);
	free(*original_bin);
}

void	handle_error(int ret, char *var, char *original_bin)
{
	if (ret == 1 || !var)
		ft_printf_e("bash: line 1: %s: %s\n", original_bin, strerror(errno));
	else
		ft_printf_e("bash: line 1: %s: command not found\n", original_bin);
}
