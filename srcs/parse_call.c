/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_call.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thgermai <thgermai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/18 16:15:55 by thgermai          #+#    #+#             */
/*   Updated: 2020/08/17 21:54:43 by thgermai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int		get_fd(char *str, int option)
{
	char		*file_name;
	int			start;
	int			i;
	int			fd;

	i = 0;
	fd = 0;
	while (str[i] && str[i] == ' ')
		i++;
	start = i;
	while (str[i] && str[i] != ' ')
		i++;
	file_name = ft_substr(str, start, i - start);
	if (option == 1)
		fd = open(file_name, O_RDONLY);
	else if (option == 2)
		fd = open(file_name, O_RDWR | O_CREAT | O_TRUNC,
			S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	else if (option == 3)
		fd = open(file_name, O_RDWR | O_CREAT | O_APPEND,
			S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	if (fd == -1)
	{
		ft_printf_e("bash: line 1: %s: %s\n", file_name, strerror(errno));    //suppression "Error"   /// JUSTE POUR LES TESTS !!!!
	//	ft_printf_e("minishell: %s: %s\n", file_name, strerror(errno));    //suppression "Error"
	}
	free(file_name);
	return (fd);
}

static int		check_input(t_call *call, int i)
{
	if (call->str[i] == '<' && !is_backslash(call->str, i -1))// && is_backslash(call->str, i-1))
	{
		if (call->in != -1)
			close(call->in);
		if ((call->in = get_fd(&call->str[i + 1], 1)) == -1)
			return (-1);
		return (1);
	}
	return (0);
}

static int		check_output(t_call *call, int i)
{
	if (call->str[i] == '>' && !is_backslash(call->str, i -1))
	{
		if (call->out != -1)
			close(call->out);
		if (call->str[i + 1] && call->str[i + 1] == '>')
		{
			if ((call->out = get_fd(&call->str[i + 2], 3)) == -1)
				return (-1);
			i++;
		}
		else if ((call->out = get_fd(&call->str[i + 1], 2)) == -1)
			return (-1);
		return (1);
	}
	return (0);
}

static void		get_args(t_call *call)
{
	int			i;
	int			start;
	char		*str;

	i = -1;
	str = NULL;
	while (call->str[++i] == ' ')
		;
	start = i;
	i--;
	while (call->str[++i])
	{
		if ((call->str[i] == '>' || call->str[i] == '<')
			&& !is_valide(call->str, i, 1) && !is_backslash(call->str, i -1))
		{
			if (start == i)
				str = NULL;
			else
				str = ft_substr(call->str, 0, i);
			free(call->str);
			call->str = str;
			return ;
		}
	}
}

static int		get_in_and_out(t_call *call, int *input, int *output)
{
	int			i;
	int			ret;

	i = -1;
	while (call->str[++i])
	{
		if (call->str[i] == '<' && !is_valide(call->str, i, 1))
		{
			ret = check_input(call, i);
			if (ret == -1)
				return (EXIT_FAILURE);
			else if (ret == 1)
				*input = 1;
		}
		if (call->str[i] == '>' && (i == 0 || call->str[i - 1] != '>')
			&& !is_valide(call->str, i, 1))
		{
			ret = check_output(call, i);
			if (ret == -1)
				return (EXIT_FAILURE);
			else if (ret == 1)
				*output = 1;
		}
	}
	return (EXIT_SUCCESS);
}

void			parse_call(t_call *call, t_list **env)
{
	int			input;
	int			output;

	input = 0;
	output = 0;
	call->env = env;
	call->in = -1;
	call->out = -1;
	get_in_and_out(call, &input, &output);
	if (!input)
		call->in = 0;
	if (!output)
		call->out = 1;
	get_args(call);
}
