/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thgermai <thgermai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/07 17:11:54 by thgermai          #+#    #+#             */
/*   Updated: 2019/11/12 11:09:32 by thgermai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_count_word(const char *s, char c)
{
	size_t			count;
	size_t			i;

	count = 0;
	i = 0;
	while (s[i])
	{
		while (s[i] && s[i] == c)
			i++;
		if (s[i] && s[i] != c)
			count++;
		while (s[i] && s[i] != c)
			i++;
	}
	if (!count)
		return (0);
	return (count);
}

static char		*ft_create_line(const char *s, char c)
{
	char			*str;
	size_t			len;

	len = 0;
	while (s[len] != c && s[len])
		len++;
	str = ft_substr(s, 0, len);
	return (str);
}

char			**ft_split(const char *s, char c)
{
	size_t			word;
	size_t			i;
	char			**tab;
	char			*temp;

	i = 0;
	if (!s)
		return (NULL);
	word = ft_count_word(s, c);
	if (!(tab = malloc(sizeof(char *) * (word + 1))))
		return (0);
	while (i < word)
	{
		while (*s == c)
			s++;
		temp = ft_create_line(s, c);
		s = s + ft_strlen(temp);
		if (!(tab[i] = ft_strdup(temp)))
			return (NULL);
		free(temp);
		i++;
	}
	tab[i] = NULL;
	return (tab);
}
