/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_f12.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thgermai <thgermai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/07 13:01:40 by thgermai          #+#    #+#             */
/*   Updated: 2019/12/01 16:36:12 by thgermai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char			*ft_strjoin_f12(char const *s1, char const *s2)
{
	size_t	s1len;
	size_t	s2len;
	char	*str;

	if (!s1 || !s2)
		return (NULL);
	s1len = 0;
	if (s1)
		s1len = ft_strlen(s1);
	s2len = ft_strlen(s2);
	if (!(str = malloc(sizeof(char) * (s1len + s2len + 1))))
		return (NULL);
	if (s1)
		ft_strlcpy(str, s1, s1len + 1);
	ft_strlcpy(str + s1len, s2, s2len + 1);
	free((char *)s1);
	free((char *)s2);
	str[s1len + s2len] = '\0';
	return (str);
}
