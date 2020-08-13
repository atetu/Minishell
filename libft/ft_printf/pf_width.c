/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_width.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thgermai <thgermai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/03 13:37:50 by thgermai          #+#    #+#             */
/*   Updated: 2020/01/08 10:59:28 by thgermai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char		*fill_width_right(char *str, t_param *param)
{
	char	*temp;

	if ((int)ft_strlen(str) > param->width)
		return (str);
	if (!(temp = malloc(sizeof(char) * (param->width - ft_strlen(str)))))
		return (NULL);
	ft_memset(temp, param->fill, param->width - ft_strlen(str));
	temp[param->width - ft_strlen(str)] = '\0';
	return (temp = ft_strjoin_f12(temp, str));
}

char		*fill_width_left(char *str, t_param *param)
{
	char	*temp;

	if ((int)ft_strlen(str) > param->width)
		return (str);
	if (!(temp = malloc(sizeof(char) * (param->width - ft_strlen(str)))))
		return (NULL);
	ft_memset(temp, param->fill, param->width - ft_strlen(str));
	temp[param->width - ft_strlen(str)] = '\0';
	return (temp = ft_strjoin_f12(str, temp));
}

char		*check_width_num(char *str, t_param *param)
{
	char	*temp;

	if (!param->width)
		return (str);
	if (param->width)
	{
		if (str[0] == '-' && param->fill == '0')
		{
			temp = ft_strdup(str + 1);
			free(str);
			param->width--;
			if (param->justify == LEFT)
				str = ft_strjoin_f2("-", fill_width_left(temp, param));
			else
				str = ft_strjoin_f2("-", fill_width_right(temp, param));
		}
		else if (param->justify == LEFT)
			str = fill_width_left(str, param);
		else
			str = fill_width_right(str, param);
	}
	return (str);
}
