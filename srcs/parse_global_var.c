/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_global_var.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/24 17:30:37 by atetu             #+#    #+#             */
/*   Updated: 2020/08/27 11:31:29 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	is_correct(char *str, int i)
{
	if (str[i] == '$' && !is_valide(str, i, 0) && (i == 0 ||
		(i > 0 && str[i - 1] != -1)) && (ft_isalnum(str[i + 1]) ||
		str[i + 1] == '_' || str[i + 1] == '{' || str[i + 1] == '?' ||
		str[i + 1] == '!' || str[i + 1] == '@' || str[i + 1] == '*' ||
		str[i + 1] == '(' || str[i + 1] == '-' || str[i + 1] == ')' ||
		str[i + 1] == '[' || str[i + 1] == '#' || str[i + 1] == '&'))
		return (1);
	return (0);
}

char		*parse_var(char *str, t_list **env)
{
	int			i;

	i = -1;
	while (str[++i])
	{
		if (is_correct(str, i))
		{
			if (!(str = check_validity(str, i, env)))
				return (NULL);
			if (!is_valide(str, i, 1) && !ft_strlen(str))
				return (clean_parse_var(&str));
			i = -1;
		}
		else if (str[i] == '~' && !is_valide(str, i, 1))
			str = fill_tilde(str, i);
	}
	return (str);
}
