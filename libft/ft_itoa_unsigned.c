/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_unsigned.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thgermai <thgermai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/08 11:40:38 by thgermai          #+#    #+#             */
/*   Updated: 2020/02/25 15:54:10 by thgermai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char			*ft_itoa_unsigned(unsigned int n)
{
	char *str;

	if (!(str = (char *)malloc(sizeof(char) * 2)))
		return (NULL);
	if (n < 0)
	{
		str[0] = '-';
		str[1] = '\0';
		str = ft_strjoin_f12(str, ft_itoa_unsigned(-n));
	}
	else if (n >= 10)
	{
		free(str);
		str = ft_strjoin_f12(ft_itoa_unsigned(n / 10),
			ft_itoa_unsigned(n % 10));
	}
	else if (n < 10 && n >= 0)
	{
		str[0] = n + 48;
		str[1] = '\0';
	}
	return (str);
}
