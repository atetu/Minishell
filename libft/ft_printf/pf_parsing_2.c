/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_parsing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thgermai <thgermai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/03 10:35:16 by thgermai          #+#    #+#             */
/*   Updated: 2020/01/09 16:56:52 by thgermai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

t_param		*set_ut_param(void)
{
	t_param *param;

	if (!(param = malloc(sizeof(t_param))))
		return (NULL);
	param->specifier = 0;
	param->precision = -1;
	param->width = 0;
	param->justify = RIGHT;
	param->fill = ' ';
	return (param);
}

int			get_value(va_list args)
{
	int		value;

	value = va_arg(args, int);
	return (value);
}

void		assigning_param(const char *str, t_param **param, va_list args)
{
	while (ft_find_in(VALID_FLAGS, *str) != -1 || ft_isdigit(*str))
	{
		if (*str == '-')
			(*param)->justify = LEFT;
		else if (*str == '.')
		{
			if (*(str + 1) == '*')
				(*param)->precision = get_value(args);
			else
				(*param)->precision = ft_atoi(str + 1);
			while (ft_isdigit(*(str + 1)) || (*(str + 1)) == '*')
				str++;
		}
		else if (*str == '0' && !(*param)->width)
			(*param)->fill = '0';
		else if (*str == '*' && !(*param)->width)
			(*param)->width = get_value(args);
		else if (!(*param)->width)
			(*param)->width = ft_atoi(str);
		str++;
	}
	(*param)->specifier = define_type(*str);
}

void		verify_param(t_param **param)
{
	if ((*param)->width < 0)
	{
		(*param)->width *= -1;
		(*param)->justify = LEFT;
	}
	if ((*param)->precision < 0)
		(*param)->precision = -1;
	if ((*param)->fill == '0' && (*param)->justify == LEFT)
		(*param)->fill = ' ';
}

t_param		*parsing_param(const char *str, va_list args)
{
	t_param		*param;

	if (*str != '%')
		return (NULL);
	if (!(param = set_ut_param()))
		return (NULL);
	str++;
	assigning_param(str, &param, args);
	verify_param(&param);
	return (param);
}
