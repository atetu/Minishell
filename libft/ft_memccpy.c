/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thgermai <thgermai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 14:45:33 by thgermai          #+#    #+#             */
/*   Updated: 2020/02/25 17:51:26 by thgermai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	size_t i;

	i = 0;
	while (i < n)
	{
		(*((unsigned char *)dst)) = ((unsigned char *)src)[i];
		dst++;
		if (((unsigned char *)src)[i] == (unsigned char)c)
			return (dst);
		i++;
	}
	return (NULL);
}
