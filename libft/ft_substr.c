/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thgermai <thgermai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/07 11:35:32 by thgermai          #+#    #+#             */
/*   Updated: 2020/01/09 21:09:32 by thgermai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*sub;

	if (!s || (start + len > ft_strlen(s)))
		return (sub = ft_strdup("\0"));
	if (!(sub = malloc(sizeof(char) * (len + 1))))
		return (NULL);
	ft_strlcpy(sub, s + start, len + 1);
	sub[len] = '\0';
	return (sub);
}
