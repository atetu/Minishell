/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thgermai <thgermai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/01 10:19:24 by thgermai          #+#    #+#             */
/*   Updated: 2020/01/09 16:16:25 by thgermai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int			ft_exit(int ret, int n, ...)
{
	va_list		argv;
	void		*temp;
	int			i;

	i = 0;
	va_start(argv, n);
	while (i < n)
	{
		if (!(temp = va_arg(argv, void *)))
			break ;
		ft_memdel(&temp);
		i++;
	}
	va_end(argv);
	return (ret);
}

void		*ft_exit_ptr(void *ret, int n, ...)
{
	va_list		argv;
	void		*temp;
	int			i;

	i = 0;
	va_start(argv, n);
	while (i < n)
	{
		if (!(temp = va_arg(argv, void *)))
			break ;
		ft_memdel(&temp);
		i++;
	}
	va_end(argv);
	return (ret);
}
