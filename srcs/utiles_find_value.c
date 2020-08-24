/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utiles_find_value.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atetu <atetu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/24 17:39:10 by atetu             #+#    #+#             */
/*   Updated: 2020/08/24 17:39:34 by atetu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static char		*free_find_value(char **tmp, char *content)
{
	free(*tmp);
	*tmp = NULL;
	return (content);
}

static int		check_option1(char *str, char *content, int opt)
{
	if (!ft_strncmp(str, content, ft_strlen(str)) && opt == 1)
		return (1);
	return (0);
}

char			*find_value(char *str, t_list **env, int opt)
{
	t_list		*current;
	char		*tmp;

	current = *env;
	while (current)
	{
		if (str[ft_strlen(str) - 1] == '=')
		{
			if (check_option1(str, (char *)current->content, opt))
				return ((char *)current->content);
			tmp = ft_substr(str, 0, ft_strlen(str) - 1);
			if (!ft_strncmp(tmp, (char *)current->content, ft_strlen(tmp)) &&
			((char *)current->content)[ft_strlen(tmp)] == '\0' && opt == 2)
				return (free_find_value(&tmp, (char*)current->content));
			free(tmp);
		}
		else
		{
			if (!ft_strncmp(str, (char *)current->content, ft_strlen(str)) &&
				((char *)current->content)[ft_strlen(str)] == '=')
				return ((char *)current->content);
		}
		current = current->next;
	}
	return (NULL);
}
