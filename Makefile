# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: user42 <user42@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/01/09 08:26:20 by thgermai          #+#    #+#              #
#    Updated: 2020/09/07 17:42:13 by user42           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
SRCSDIR = srcs
OBJSDIR = .objs
SRCS = main.c\
		builtin_cd_pwd.c\
		builtin_echo.c\
		builtin_env.c\
		builtin_env_utiles.c\
		builtin_env_add.c\
		builtin_env_export.c\
		builtin_env_unset.c\
		builtin_exit.c\
		clean.c\
		execute.c\
		execute_utiles.c\
		handle_pipes.c\
		parse_call.c\
		parse_exec.c\
		parse_pipes.c\
		parse_semicolons.c\
		parse_semicolons_utiles.c\
		parse_semicolons_utiles_errors.c\
		prompt.c\
		prompt_utiles.c\
		shlvl.c\
		signal.c\
		utiles.c\
		utiles_is_valid.c\
		utiles_convert.c\
		parse_global.c\
		parse_call_utiles.c\
		utiles_find_value.c\
		parse_exec_utiles.c\
		parse_global_marks.c\
		parse_global_var.c\
		parse_global_var_fill.c\
		parse_global_var_validity.c\
		parse_global_var_weird.c\
		parse_global_var_weird_utiles.c\
		parse_global_var_utiles.c\
		parse_global_args.c\
		get_input.c
OBJS = $(addprefix $(OBJSDIR)/, $(SRCS:.c=.o))
DPDCS = $(OBJS:.o=.d)
INCLUDES = -I includes/ -I libft/
LIB = libft/libft.a
CFLAGS = -Wall -Wextra -Werror
LOGFILE = $(LOGPATH) `date +'%y.%m.%d %H:%M:%S'`
MSG = ---

opti :
	@(make -j all)

all : $(NAME)

-include $(DPDCS)

fg : $(LIB) $(OBJS)
	@(clang $(CFLAGS) $(OBJS) $(LIB) $(INCLUDES) -o $(NAME))
	@(echo "$(NAME) created")

$(NAME) : $(LIB) $(OBJS)
	@(clang $(CFLAGS) $(OBJS) $(LIB) $(INCLUDES) -o $(NAME))
	@(echo "$(NAME) created")

$(LIB) :
	@(make -C libft)

$(OBJSDIR)/%.o : $(SRCSDIR)/%.c | $(OBJSDIR)
	@(echo "Compiling -> $^")
	@(clang $(CFLAGS) $(INCLUDES) -MMD -c $< -o $@)

$(OBJSDIR) :
	@(mkdir -p .objs)

clean :
	@(rm -f $(NAME))
	@(make clean -C libft/)

fclean : clean
	@(rm -rf $(OBJSDIR))
	@(make fclean -C libft/)

git : fclean
	@(make fclean -C libft)
	@(git add *)
	@(git commit -m "$(LOGFILE): $(MSG)")
	@(git push)

re : fclean all

