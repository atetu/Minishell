# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: atetu <atetu@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/01/09 08:26:20 by thgermai          #+#    #+#              #
#    Updated: 2020/08/24 18:09:28 by atetu            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
SRCSDIR = srcs
OBJSDIR = .objs
SRCS = main.c\
		builtin.c\
		builtin_env.c\
		builtin_env_utiles.c\
		builtin_exit.c\
		clean.c\
		execute.c\
		execute_utiles.c\
		handle_pipes.c\
		parse_call.c\
		parse_exec.c\
		parse_pipes.c\
		parse_semicolons.c\
		prompt.c\
		shlvl.c\
		signal.c\
		utiles.c\
		utiles_convert.c\
		parse_global.c\
		parse_call_utiles.c\
		utiles_find_value.c\
		parse_exec_utiles.c\
		parse_global_marks.c\
		parse_global_var.c\
		parse_global_var_utiles.c\
		parse_global_args.c\
		builtin_env_add.c\
		builtin_env_export.c\
		builtin_env_unset.c
OBJS = $(addprefix $(OBJSDIR)/, $(SRCS:.c=.o))
DPDCS = $(OBJS:.o=.d)
INCLUDES = -I includes/ -I libft/
LIB = libft/libft.a
CFLAGS = -Wall -Wextra -Werror -g3 -fsanitize=address
LOGFILE = $(LOGPATH) `date +'%y.%m.%d %H:%M:%S'`
MSG = ---

opti :
	@(make -j all)

all : $(NAME)

-include $(DPDCS)

fg : $(LIB) $(OBJS)
	@(gcc $(CFLAGS) -g3 -fsanitize=address $(OBJS) $(LIB) $(INCLUDES) -o $(NAME))
	@(echo "$(NAME) created")

$(NAME) : $(LIB) $(OBJS)
	@(gcc $(CFLAGS) $(OBJS) $(LIB) $(INCLUDES) -o $(NAME))
	@(echo "$(NAME) created")

$(LIB) :
	@(make -C libft)

$(OBJSDIR)/%.o : $(SRCSDIR)/%.c | $(OBJSDIR)
	@(echo "Compiling -> $^")
	@(gcc $(CFLAGS) $(INCLUDES) -MMD -c $< -o $@)

$(OBJSDIR) :
	@(mkdir -p .objs)

clean :
	@(rm -f $(NAME))

fclean : clean
	@(rm -rf $(OBJSDIR))

git : fclean
	@(make fclean -C libft)
	@(git add *)
	@(git commit -m "$(LOGFILE): $(MSG)")
	@(git push)

re : fclean all

