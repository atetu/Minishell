/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atetu <atetu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/16 10:53:30 by thgermai          #+#    #+#             */
/*   Updated: 2020/08/25 10:15:38 by atetu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include <unistd.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <stdlib.h>
# include <fcntl.h>
# include <errno.h>
# include <string.h>
# include <signal.h>

# define REPLACE_CHAR "\\\"'$"

typedef	struct		s_call
{
	char			*str;
	int				in;
	int				out;
	t_list			**env;
	int				ret;
}					t_call;

/*
**	-- Global Variables --
*/

pid_t				*g_pids;
int					g_exit_status;
int					g_exit_nb;
char				*g_pwd;
char				*g_oldpwd;
int					g_ret;
char				*g_home;
char				*g_last;

/*
**	-- Functions --
*/

void				control_c(int sig);
int					control_d(void);
void				control_quit(int sig);
void				prompt(char **env);
char				**parse_semicolon(char *str);
int					get_n_pipes(char *args, int option);
void				parse_pipes(char *str, t_call *calls);
void				parse_call(t_call *call, t_list **env);
int					create_pipes(t_call *calls, int pipes[][2]);
void				connect_pipes(t_call *calls, int pipes[][2], int n_pipes);
pid_t				exec1(t_call *call, int pipes[][2], int size,
	int *exit_info);
void				exec2(t_call *call, int *exit_info);
void				wait_pids(pid_t *pids, int size, t_call *calls);
char				*parse_exec(t_call *call, char *bin);
void				duplicate_fd(t_call *call);
int					execute(t_call *call, char **func, char **env,
	int *exit_info);
void				exec_knonw(t_call *call, char **func, char **var_env,
	int *exit_info);
void				handle_shlvl(t_list **list);
char				**parse(char *str, t_list **env);

/*
** Builtins
*/

int					ft_pwd(void);
int					ft_cd(char **func, t_call *call);
int					ft_echo(char **func);
int					ft_unset(t_call *call, char **func);
int					ft_env(t_call *call, char **func);
int					ft_export(t_call *call, char **func);
int					add_env(t_call *call, char *key, char *value, int option);
char				*get_key(char *str);
int					delete_element(t_call *call, char *key);
t_list				**sort_var_env(t_list **env);
int					ft_builtin_exit(char **func, int *exit_info);

/*
**	-- Utiles functions --
*/

t_list				**tab_to_list(char **env);
char				**list_to_tab(t_list **lst);
void				print(void);
int					is_valide(char *str, int index, int option);
int					is_backslash(char *str, int index);
int					known_func(char *str);
char				*find_value(char *str, t_list **env, int opt);
char				*get_cwd(void);
void				clean_calls(t_call *calls);
void				close_pipes(int pipes[][2], int size);
void				clean_array(char **array);
void				clear_all(char *args, t_list **list);


/*
** Rajout Alice
*/

int					get_fd(char *str, int option);
void				refresh_var_underscore(char **func, t_call *call);
int					check_call_in(int in);
int					check_double_points(char *original_bin);
int					check_existing_path(char **path, char ***paths,
						char **bin, char **original_bin);
char				*check_is_file(char *bin, char *original_bin);
void				clean_exec(char **paths[], char **bin, char **original_bin);
void				handle_error(int ret, char *var, char *original_bin);
void				manage_pipes(t_call *calls, int pipes[][2],
						char *str, int *exit_info);
char				*delete_marks(char *str, int j);
char				*replace_marks(char *str);
char				*parse_var(char *str, t_list **env);
char				*get_var_name(char *str);
char				*get_var_value(char *key, t_list **env);
char				*create_new_str(char *str, char *key, char *value,
						int index);
char				*create_new_str2(char *str, char *key, char *value,
						int index);
char				*parse_arg(char *str, t_list **env);
int					get_n_args(char *str);
int					check_closed(char *str);
void				parse_quotes(char *str);
int					ft_env1(t_call *call);


/*
** Rajout Thomas
*/

void				add_env2(t_call *call, char *key, char *value);



#endif
