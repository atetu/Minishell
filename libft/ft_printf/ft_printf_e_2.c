/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_e.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thgermai <thgermai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/03 08:41:57 by thgermai          #+#    #+#             */
/*   Updated: 2020/02/24 10:51:57 by thgermai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int				redict_type_e(va_list args, t_param *param)
{
	int		(*fptr[9])(va_list, t_param *);

	if (!param)
		return (ft_exit(-1, 0));
	if (param->specifier < 0)
		return (ft_exit(-1, 1, param));
	fptr[0] = &pf_fill_char_e;
	fptr[1] = &pf_fill_str_e;
	fptr[2] = &pf_fill_add_e;
	fptr[3] = &pf_fill_deci_e;
	fptr[4] = &pf_fill_int_e;
	fptr[5] = &pf_fill_unsi_e;
	fptr[6] = &pf_fill_hexa_e;
	fptr[7] = &pf_fill_hexa_caps_e;
	fptr[8] = &pf_fill_modulo_e;
	return ((*fptr[param->specifier])(args, param));
}

int				print_str_e(const char *str, int i)
{
	char		*output;

	if (!(output = ft_substr(str, 0, next_arg_index(str))))
		return (ft_exit(-1, 0));
	ft_putstr_fd(output, 2);
	return (ft_exit(i + ft_strlen(output), 1, output));
}

int				ft_printf_e(const char *str, ...)
{
	va_list		args;
	int			i;
	int			ret;

	i = 0;
	ret = 0;
	va_start(args, str);
	while (*str)
	{
		if ((i = print_str_e(str, i)) == -1)
			break ;
		if (str[next_arg_index(str)] == '%')
		{
			if ((ret = redict_type_e(args, parsing_param(str +
				next_arg_index(str), args))) == -1)
			{
				i = -1;
				break ;
			}
			i += ret;
		}
		str = ft_refresh_str(str);
	}
	va_end(args);
	return (ft_exit(i, 0));
}
