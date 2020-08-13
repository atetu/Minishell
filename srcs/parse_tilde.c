#include "../includes/minishell.h"

char     		*find_user(char *str, t_list **env)
{
    char        *tmp;
    char		*var;
	char		*user;

    tmp = NULL;
    var = NULL;
    var = find_value("USER", env, 1);
	user = ft_substr(var, 5, ft_strlen(var) - 5);
    if (user)
		tmp = ft_strjoin("/Users/", user);
    if (str)
    {
		tmp = ft_strjoin_f1(tmp, str);
   //     tmp = ft_strjoin_f2("/", tmp);
    }
    return (tmp);
}

char			*parse_tilde(char *str, t_list **env)
{
	if (str[0] == '~')
    {
        if (str[1] && str[1] != ' ' && str[1] != '/')
            ;
        else
            str = find_user(str + 1, env); 
    }
    return (str);
}
