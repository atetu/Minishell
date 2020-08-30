/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_precision.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thgermai <thgermai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/03 09:26:21 by thgermai          #+#    #+#             */
/*   Updated: 2020/01/08 10:59:24 by thgermai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char			*fill_precision(char *str, t_param *param)
{
	char		*temp;

	if ((int)ft_strlen(str) >= param->precision)
		return (str);
	if (!(temp = malloc(sizeof(char) *
		(param->precision - ft_strlen(str)))))
		return (NULL);
	ft_memset(temp, '0', param->precision - ft_strlen(str));
	temp[param->precision - ft_strlen(str)] = '\0';
	return (temp = ft_strjoin_f12(temp, str));
}

char			*check_precision_num(char *str, t_param *param)
{
	char *temp;

	temp = NULL;
	if (param->precision != -1)
	{
		if (str[0] == '-')
		{
			temp = ft_strdup(str + 1);
			free(str);
			str = ft_strjoin_f2("-", fill_precision(temp, param));
		}
		else
			str = fill_precision(str, param);
	}
	return (str);
}
