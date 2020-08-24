/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env_utiles.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atetu <atetu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/02 22:52:48 by thgermai          #+#    #+#             */
/*   Updated: 2020/08/24 17:57:36 by atetu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char			*get_key(char *str)
{
	int			i;

	i = -1;
	while (str[++i])
		if (str[i] == '=')
			break ;
	if (str[i] == '=')
		return (ft_substr(str, 0, i + 1));
	return (ft_strjoin_f1(ft_substr(str, 0, i), "="));
}

int				delete_element(t_call *call, char *key)
{
	t_list		*current;
	t_list		*previous;

	current = *call->env;
	previous = current;
	while (current)
	{
		if (!ft_strncmp(key, (char *)current->content, ft_strlen(key)))
		{
			if (previous == current)
				call->env = &(current->next);
			else
				previous->next = current->next;
			ft_lstdelone(current, free);
			return (EXIT_SUCCESS);
		}
		previous = current;
		current = current->next;
	}
	return (EXIT_FAILURE);
}

static t_list	**copy_list(t_list **old_list)
{
	t_list		**list;
	t_list		*current;

	current = *old_list;
	if (!(list = malloc(sizeof(t_list *))))
		return (NULL);
	*list = NULL;
	while (current)
	{
		ft_lstadd_back(list, ft_lstnew(ft_strdup((char *)current->content)));
		current = current->next;
	}
	return (list);
}

static void		swap(t_list *s1, t_list *s2)
{
	void		*temp;

	temp = s1->content;
	s1->content = s2->content;
	s2->content = temp;
}

t_list			**sort_var_env(t_list **env)
{
	t_list		**list;
	char		*key1;
	char		*key2;
	t_list		*current;
	t_list		*next;

	list = copy_list(env);
	current = *list;
	while (current->next)
	{
		next = current->next;
		key1 = get_key((char *)current->content);
		key2 = get_key((char *)next->content);
		if (ft_strncmp(key1, key2, ft_strlen(key1) > ft_strlen(key2) ?
			ft_strlen(key1) : ft_strlen(key2)) > 0)
		{
			swap(current, next);
			current = *list;
		}
		else
			current = current->next;
		free(key1);
		free(key2);
	}
	return (list);
}
