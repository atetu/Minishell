/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_global_var_weird_utiles.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/27 11:27:22 by user42            #+#    #+#             */
/*   Updated: 2020/08/27 11:28:12 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int			handle_brackets(char *str, int i, char **key, char **value)
{
	int		j;
	char	*tmp;

	tmp = NULL;
	j = i + 2;
	while (str[j] && str[j] != ']')
		j++;
	if (!is_valide(str, j, 0) && str[j - 1] != -1)
	{
		tmp = ft_substr(str, i + 1, j - i);
		*key = ft_strjoin_f1(tmp, "=");
		*value = ft_strdup("0");
		return (1);
	}
	else
		return (0);
}

int			clean_weird(char **key, char **value, char ***str, char **new_str)
{
	free(*key);
	free(*value);
	free(**str);
	**str = *new_str;
	return (1);
}

void		check_null_value(char **value)
{
	if (!(*value))
		*value = ft_strdup("");
}
