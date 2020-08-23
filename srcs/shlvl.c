/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shlvl.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thgermai <thgermai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/15 18:30:08 by alicetetu         #+#    #+#             */
/*   Updated: 2020/08/17 15:36:44 by thgermai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void		pass_sign(char *shlvl_str, int *i, int *j)
{
	if (shlvl_str[*i] == '-' || shlvl_str[*i] == '+')
	{
		if (shlvl_str[*i] == '+')
			*j = 1;
		(*i)++;
	}
}

static void		check_shlvl_nb(char *shlvl_str, t_list *current)
{
	int		shlvl_nb;
	char	*tmp;

	tmp = NULL;
	shlvl_nb = ft_atoi(shlvl_str);
	if (shlvl_nb < 0)
	{
		free(current->content);
		current->content = (void *)ft_strdup("SHLVL=0");
	}
	else if (shlvl_nb == 0)
	{
		free(current->content);
		current->content = (void *)ft_strdup("SHLVL=1");
	}
	else if (shlvl_nb > 0)
	{
		shlvl_nb++;
		tmp = ft_itoa(shlvl_nb);
		free(current->content);
		current->content = (void *)ft_strjoin("SHLVL=", tmp);
		if (tmp)
			free(tmp);
	}
}

static int		adapt_shlvl_var(t_list *current)
{
	char	*shlvl_str;
	char	*tmp;
	int		i;
	int		j;

	tmp = NULL;
	shlvl_str = ft_substr((char*)current->content, 6,
		(ft_strlen((char*)current->content) - 6));
	i = 0;
	j = 0;
	pass_sign(shlvl_str, &i, &j);
	while (shlvl_str[i] && (ft_isdigit((int)(shlvl_str[i])) == 1))
		i++;
	if (shlvl_str[i] == '\0')
		check_shlvl_nb(&(shlvl_str[j]), current);
	else
	{
		free(current->content);
		current->content = (void *)ft_strdup("SHLVL=1");
	}
	free(shlvl_str);
	return (1);
}

void			handle_shlvl(t_list **list)
{
	t_list	**tmp;
	t_list	*current;
	int		is_shlvl;

	tmp = list;
	current = *tmp;
	is_shlvl = 0;
	while (current)
	{
		if (!(strncmp((char *)current->content, "SHLVL=", 6)))
		{
			is_shlvl = adapt_shlvl_var(current);
			break ;
		}
		current = current->next;
	}
	if (!is_shlvl)
		ft_lstadd_back(list, ft_lstnew(ft_strdup("SHLVL=1")));
}
