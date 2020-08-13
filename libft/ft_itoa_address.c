/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_address.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thgermai <thgermai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/01 10:49:36 by thgermai          #+#    #+#             */
/*   Updated: 2019/12/02 17:00:23 by thgermai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

char			*ft_itoa_address(unsigned long long int n)
{
	char		*str;
	char		*base;

	base = ft_strdup("0123456789abcdef");
	if (!(str = (char *)ft_calloc(sizeof(char), 2)))
		return (NULL);
	else if (n >= 16)
	{
		free(str);
		str = ft_strjoin_f12(ft_itoa_address(n / 16),
			ft_itoa_address(n % 16));
	}
	else if (n < 16 && n >= 0)
	{
		str[0] = base[n];
		str[1] = '\0';
	}
	free(base);
	return (str);
}
