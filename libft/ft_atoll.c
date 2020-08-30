/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoll.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/30 12:04:52 by user42            #+#    #+#             */
/*   Updated: 2020/08/30 12:47:12 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static int				ft_space(char c)
{
	if (c == '\t' || c == '\n' || c == '\r'
		|| c == '\v' || c == '\f' || c == ' ')
		return (1);
	else
		return (0);
}

unsigned long long		ft_atoll(const char *str)
{
	long long				i;
	long long				neg;
	unsigned long long		total;
	unsigned long long		max;

	total = 0;
	neg = 1;
	i = 0;
	max = 9223372036854775807;
	while (ft_space(str[i]))
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			neg = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		total = (total * 10) + (str[i] - 48);
		i++;
	}
	if ((neg < 0 && total > (max + 1)) || (neg > 0 && total > max))
		return (max + 2);
	return (total);
}
