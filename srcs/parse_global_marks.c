/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_global_marks.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atetu <atetu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/24 17:27:10 by atetu             #+#    #+#             */
/*   Updated: 2020/08/24 17:27:13 by atetu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char		*delete_marks(char *str, int j)
{
	int			i;
	char		*new_str;

	if (!(new_str = malloc(sizeof(char) * (j + 1))))
		return (NULL);
	i = -1;
	j = 0;
	while (str[++i])
	{
		if (str[i] < 0)
			;
		else
			new_str[j++] = str[i];
	}
	new_str[j] = '\0';
	return (new_str);
}

char		*replace_marks(char *str)
{
	int			i;
	int			j;
	char		*new_str;

	i = -1;
	j = 0;
	while (str[++i])
		if (str[i] > 0)
			j++;
	if (!j)
	{
		free(str);
		return (ft_strdup(""));
	}
	new_str = delete_marks(str, j);
	free(str);
	return (new_str);
}
