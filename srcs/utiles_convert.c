/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utiles_convert.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atetu <atetu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/02 22:40:46 by thgermai          #+#    #+#             */
/*   Updated: 2020/08/12 14:09:44 by atetu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char			**list_to_tab(t_list **lst)
{
	char		**tab;
	int			i;
	int			size;
	t_list		*current;

	size = ft_lstsize(*lst);
	i = -1;
	if (!(tab = malloc(sizeof(char *) * (size + 1))))
	{
		ft_printf_e("Minishell: error: malloc failed\n");
		exit(EXIT_FAILURE);
	}
	current = *lst;
	while (++i < size)
	{
		tab[i] = (char *)current->content;
		current = current->next;
	}
	tab[i] = NULL;
	return (tab);
}

t_list			**tab_to_list(char **env)
{
	int			i;
	t_list		**list;
	t_list		**tmp;
	t_list *current;
	int lev ;
	char *lev_str;
//	char *dest;

	i = -1;
	lev =0;
	if (!(list = malloc(sizeof(t_list *))))
	{
		ft_printf_e("Minishell: error: malloc failed\n");
		exit(EXIT_FAILURE);
	}
	*list = NULL;
	while (env[++i])
	{
		if (!(ft_strncmp(env[i], "OLDPWD=", 7)))
			ft_lstadd_back(list, ft_lstnew(ft_strdup("OLDPWD")));
		else
			ft_lstadd_back(list, ft_lstnew(ft_strdup(env[i])));
	}
	tmp = list;
	current = *tmp;
	while (current)
	{
		if (!(strncmp((char *)current->content, "SHLVL=", 6)))
		{
			lev = ft_atoi(ft_substr((char*)current->content, 6, (ft_strlen((char*)current->content) - 6)));
			if (lev < 0)
			{
				free(current->content);
				current->content = (void *) ft_strdup("SHLVL=0");
			}
			else if (lev == 0)
				current->content = (void *) ft_strdup("SHLVL=1");
			else if (lev > 0)
			{
				lev++;
				lev_str = ft_itoa(lev);
				current->content = (void *) ft_strjoin("SHLVL=", lev_str);
			}
			lev = 1;
			break;
		}
		current = current->next;
	}
	if (lev ==0)
		ft_lstadd_back(list, ft_lstnew(ft_strdup("SHLVL=1")));
	return (list);
}
