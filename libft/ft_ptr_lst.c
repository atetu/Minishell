/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ptr_lst.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thgermai <thgermai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/15 18:16:03 by thgermai          #+#    #+#             */
/*   Updated: 2020/02/24 10:37:55 by thgermai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		ft_free_ptrlst(t_list **lst)
{
	t_list		*current;
	t_ptrlst	*ptr;

	ptr = NULL;
	current = *lst;
	while (current)
	{
		ptr = current->content;
		(ptr->fptr)(ptr->ptr);
		ptr->ptr = NULL;
		current = current->next;
	}
	ft_lstclear(lst, free);
	free(lst);
}

void		join_elem(t_list **lst, t_list *last, t_list *current)
{
	if (last)
	{
		last->next = current->next;
		ft_lstdelone(current, free);
	}
	else
	{
		*lst = current->next;
		ft_lstdelone(current, free);
	}
}

void		ft_del_ptr(t_list **lst, void *to_del)
{
	t_list		*last;
	t_list		*current;
	t_ptrlst	*ptr;

	current = *lst;
	last = NULL;
	while (current)
	{
		ptr = current->content;
		if (ptr->ptr == to_del)
		{
			(ptr->fptr)(ptr->ptr);
			join_elem(lst, last, current);
			return ;
		}
		last = current;
		current = current->next;
	}
}

void		*ft_add_ptr(void *ptr, t_list **lst, void (*fptr)(void *))
{
	t_ptrlst	*new_ptr;
	t_list		*new_elem;

	if (!(new_ptr = ft_calloc(sizeof(t_ptrlst), 1)))
		return (NULL);
	new_ptr->ptr = ptr;
	new_ptr->fptr = fptr;
	new_elem = ft_lstnew(new_ptr);
	ft_lstadd_back(lst, new_elem);
	return (ptr);
}

void		ft_print_add_lst(t_list **lst)
{
	t_ptrlst	*ptr;
	t_list		*current;

	current = *lst;
	while (current)
	{
		ptr = current->content;
		ft_printf("->%p\n", current->content);
		current = current->next;
	}
}
