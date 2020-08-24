/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utiles_convert.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atetu <atetu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/02 22:40:46 by thgermai          #+#    #+#             */
/*   Updated: 2020/08/24 17:40:24 by atetu            ###   ########.fr       */
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

static int		is_pwd_oldpwd(char *env, t_list **list, int *is_pwd,
	int *is_oldpwd)
{
	//char *tmp;  // tous les commentaires pour la version VM

//	tmp = NULL;
	if (!(ft_strncmp(env, "OLDPWD=", 7)))   // dans VM garde le oldpwd qu'on lui envoie a condition que ce soit un vrai chemin
	{
	//	tmp = ft_substr(env, 7, ft_strlen(env) - 7);
	//	if (chdir(tmp)==0)
	//	{
	//		chdir(g_pwd);
	//		ft_lstadd_back(list, ft_lstnew(ft_strdup(env)));
		//	*is_oldpwd = 1;
	//		free(g_oldpwd);
		//	g_oldpwd = tmp;
	//	}
		ft_lstadd_back(list, ft_lstnew(ft_strdup("OLDPWD")));
		*is_oldpwd = 1;
		return (1);
	}
	if (!(ft_strncmp(env, "PWD=", 4)))
	{
		ft_lstadd_back(list, ft_lstnew(ft_strjoin("PWD=", g_pwd)));
		*is_pwd = 1;
		return (1);
	}
	return (0);
}

static void		add_remaining_var(t_list **list, int is_oldpwd, int is_pwd)
{
	if (!is_oldpwd)
		ft_lstadd_back(list, ft_lstnew(ft_strdup("OLDPWD")));
	if (!is_pwd)
		ft_lstadd_back(list, ft_lstnew(ft_strjoin("PWD=", g_pwd)));
//	ft_lstadd_back(list, ft_lstnew(ft_strdup("LESSCLOSE=/usr/bin/lesspipe %s %s"));  VAR A AJPOUTER DANS LA VM
//	ft_lstadd_back(list, ft_lstnew(ft_strdup("LESSOPEN=| usr/bin/lesspipe %s"));
}

t_list			**tab_to_list(char **env)
{
	int			i;
	t_list		**list;
	int is_oldpwd;
	int is_pwd;

	i = -1;
	is_oldpwd = 0;
	is_pwd = 0;
	if (!(list = malloc(sizeof(t_list *))))
	{
		ft_printf_e("Minishell: error: malloc failed\n");
		exit(EXIT_FAILURE);
	}
	*list = NULL;
	while (env[++i])   // si aucune var d'env n'est envoyee au lancement du bash, PWD, OLDPWD et SHLVL sont creees. Seule SHLVL reprend la valeur envoyee le cas echeant au bash
	{
		if (!(is_pwd_oldpwd(env[i], list, &is_pwd, &is_oldpwd))) // derniere condition pour var _= qui semble supprimee dans le bash
			ft_lstadd_back(list, ft_lstnew(ft_strdup(env[i])));
	}
	add_remaining_var(list, is_oldpwd, is_pwd);
	handle_shlvl(list);
	return (list);
}
