/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_fill_1_5_e.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thgermai <thgermai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/01 14:13:41 by thgermai          #+#    #+#             */
/*   Updated: 2020/02/25 17:46:02 by thgermai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int				pf_fill_char_e(va_list args, t_param *param)
{
	char	c;
	char	*temp;

	c = va_arg(args, int);
	if (!(temp = ft_calloc(1, 1)))
		return (ft_exit(-1, 1, param));
	if (param->width)
	{
		param->width--;
		if (param->justify == LEFT)
		{
			temp = fill_width_left(temp, param);
			write(1, &c, 1);
			ft_putstr_fd(temp, 2);
		}
		else
		{
			temp = fill_width_right(temp, param);
			ft_putstr_fd(temp, 2);
			write(2, &c, 1);
		}
	}
	else
		write(2, &c, 1);
	return (ft_exit(param->width + 1, 2, temp, param));
}

int				pf_fill_str_e(va_list args, t_param *param)
{
	char	*str;
	char	*temp;

	if (!(str = va_arg(args, char *)))
		str = ft_strdup("(null)");
	else
		str = ft_strdup(str);
	if (param->precision != -1 && param->precision < (int)ft_strlen(str))
		temp = ft_substr(str, 0, param->precision);
	else if (!param->precision)
		temp = ft_strdup("");
	else
		temp = ft_strdup(str);
	if (param->width)
	{
		if (param->justify == LEFT)
			temp = fill_width_left(temp, param);
		else
			temp = fill_width_right(temp, param);
	}
	ft_putstr_fd(temp, 2);
	return (ft_exit(ft_strlen(temp), 3, str, temp, param));
}

int				pf_fill_add_e(va_list args, t_param *param)
{
	void	*ptr;
	char	*result;

	ptr = va_arg(args, void *);
	if (!param->precision)
		result = ft_strdup("");
	else if (!ptr)
		result = ft_strdup("0");
	else
		result = ft_itoa_address((unsigned long long int)ptr);
	if (param->precision != -1 && param->precision)
	{
		result = fill_precision(result, param);
		param->fill = ' ';
	}
	result = ft_strjoin_f2("0x", result);
	result = check_width_num(result, param);
	ft_putstr_fd(result, 2);
	return (ft_exit(ft_strlen(result), 2, result, param));
}

int				pf_fill_deci_e(va_list args, t_param *param)
{
	int		i;
	char	*num;

	if ((i = va_arg(args, int)))
		num = ft_itoa(i);
	else if (!i && !param->precision)
		num = ft_strdup("");
	else
		num = ft_itoa(0);
	if (param->precision != -1)
	{
		num = check_precision_num(num, param);
		param->fill = ' ';
	}
	num = check_width_num(num, param);
	ft_putstr_fd(num, 2);
	return (ft_exit(ft_strlen(num), 2, num, param));
}

int				pf_fill_int_e(va_list args, t_param *param)
{
	int		i;
	char	*num;

	if ((i = va_arg(args, int)))
		num = ft_itoa(i);
	else if (!i && !param->precision)
		num = ft_strdup("");
	else
		num = ft_itoa(0);
	if (param->precision != -1)
	{
		num = check_precision_num(num, param);
		param->fill = ' ';
	}
	num = check_width_num(num, param);
	ft_putstr_fd(num, 2);
	return (ft_exit(ft_strlen(num), 2, num, param));
}
