/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thgermai <thgermai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/12 11:41:51 by thgermai          #+#    #+#             */
/*   Updated: 2020/02/25 17:45:47 by thgermai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list		*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list		*new_elem;
	t_list		*new_list;
	t_list		*origin;

	origin = lst;
	if (!lst)
		return (NULL);
	if (!(new_elem = ft_lstnew(f(lst->content))))
		return (NULL);
	new_list = new_elem;
	while (lst->next)
	{
		lst = lst->next;
		if (!(new_elem = ft_lstnew(f(lst->content))))
		{
			ft_lstclear(&new_list, del);
			return (NULL);
		}
		ft_lstadd_back(&new_list, new_elem);
		new_elem = NULL;
	}
	ft_lstclear(&origin, del);
	return (new_list);
}
