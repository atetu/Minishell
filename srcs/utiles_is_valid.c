/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utiles_is_valid.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/04 13:50:56 by user42            #+#    #+#             */
/*   Updated: 2020/09/05 11:28:20 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int				is_valide(char *str, int index, int option)
{
	int			i;
	int			in_quote;
	int			in_dquote;

	i = 0;
	in_quote = 0;
	in_dquote = 0;
	while (str[i] && i < index)
	{
		if (str[i] == '"' && (i == 0 || (i > 0 && (str[i - 1] != -1)))
			&& !in_quote)
			in_dquote == 1 ? in_dquote-- : in_dquote++;
		else if (str[i] == '\'' && (i == 0 || (i > 0 && (str[i - 1] != -1)))
			&& !in_dquote)
			in_quote == 1 ? in_quote-- : in_quote++;
		i++;
	}
	if (!option && str[i] && !in_quote)
		return (EXIT_SUCCESS);
	if (option && !in_quote && !in_dquote)
		return (EXIT_SUCCESS);
	return (EXIT_FAILURE);
}

int				is_valide2(char *str, int index, int option)
{
	int			i;
	int			in_quote;
	int			in_dquote;

	i = 0;
	in_quote = 0;
	in_dquote = 0;
	while (str[i] && i < index)
	{
		if (str[i] == '"' && (i == 0 || (i > 0 && (str[i - 1] != '\\')))
			&& !in_quote)
			in_dquote == 1 ? in_dquote-- : in_dquote++;
		else if (str[i] == '\'' && (i == 0 || (i > 0 && (str[i - 1] != '\\')))
			&& !in_dquote)
			in_quote == 1 ? in_quote-- : in_quote++;
		i++;
	}
	if (!option && str[i] && !in_quote)
		return (EXIT_SUCCESS);
	if (option && !in_quote && !in_dquote)
		return (EXIT_SUCCESS);
	return (EXIT_FAILURE);
}
