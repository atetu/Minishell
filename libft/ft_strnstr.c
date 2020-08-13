/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thgermai <thgermai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/05 17:25:15 by thgermai          #+#    #+#             */
/*   Updated: 2019/11/10 10:29:40 by thgermai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	count;

	count = 0;
	if (!needle[0])
		return ((char *)haystack);
	while (*haystack && count <= len)
	{
		i = 0;
		while (needle[i] && haystack[i] && haystack[i] == needle[i])
			i++;
		if (!needle[i] && i + count <= len)
			return ((char *)haystack);
		haystack++;
		count++;
	}
	return (NULL);
}
