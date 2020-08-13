# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: atetu <atetu@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/01/09 08:26:20 by thgermai          #+#    #+#              #
#    Updated: 2020/08/03 12:01:09 by atetu            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
SRCSDIR = srcs
OBJSDIR = .objs
SRCS = main.c\
		builtin.c\
		builtin_env.c\
		builtin_env_utiles.c\
		clean.c\
		execute.c\
		execute_utiles.c\
		handle_pipes.c\
		parse_call.c\
		parse_exec.c\
		parse_func.c\
		parse_pipes.c\
		parse_quotes.c\
		parse_semicolons.c\
		parse_tilde.c\
		parse_var.c\
		prompt.c\
		prompt_utiles.c\
		signal.c\
		utiles.c\
		utiles_convert.c
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

