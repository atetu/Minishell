/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_base.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thgermai <thgermai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/26 15:05:14 by thgermai          #+#    #+#             */
/*   Updated: 2019/11/26 15:17:07 by thgermai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_check_base(char *base)
{
	int i;
	int j;

	i = 0;
	while (base[i])
	{
		j = i + 1;
		while (base[i] != base[j] && base[j])
			j++;
		if ((base[i] == base[j]) || !((base[i] >= 'a' && base[i] <= 'z') ||
				(base[i] >= 'A' && base[i] <= 'Z') || (base[i] >= '0' &&
				base[i] <= '9')))
			return (0);
		i++;
	}
	if (i <= 1)
		return (0);
	return (1);
}

void	ft_putnbr_base(int nbr, char *base)
{
	unsigned int	n;
	size_t			i;

	i = 0;
	if (ft_check_base(base) == 0)
		return ;
	if (nbr < 0)
	{
		ft_putchar_fd('-', 1);
		n = -nbr;
	}
	else
		n = nbr;
	if (nbr >= (int)ft_strlen(base))
		ft_putnbr_base(nbr / ft_strlen(base), base);
	ft_putchar_fd(base[nbr % ft_strlen(base)], 1);
}
