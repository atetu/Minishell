# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: atetu <atetu@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/09/03 14:34:05 by thgermai          #+#    #+#              #
#    Updated: 2020/08/03 15:04:55 by atetu            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a
OBJSDIR = .objs
SRCS = get_next_line.c\
	ft_find_in.c\
	ft_atoi.c\
	ft_atoll.c\
   	ft_memchr.c\
	ft_strlen.c\
	ft_bzero.c\
	ft_memcmp.c\
	ft_strncmp.c\
	ft_isalnum.c\
	ft_memcpy.c\
	ft_strnstr.c\
	ft_isalpha.c\
	ft_memmove.c\
	ft_strrchr.c\
	ft_isascii.c\
	ft_memset.c\
	ft_tolower.c\
	ft_isdigit.c\
	ft_strchr.c\
	ft_toupper.c\
	ft_isprint.c\
	ft_strlcat.c\
	ft_memccpy.c\
	ft_strlcpy.c\
	ft_calloc.c\
	ft_strdup.c\
	ft_substr.c\
	ft_strjoin.c\
	ft_strjoin_f1.c\
	ft_strjoin_f2.c\
	ft_strjoin_f12.c\
	ft_strtrim.c\
	ft_putchar_fd.c\
	ft_putendl_fd.c\
	ft_putnbr_base.c\
	ft_putnbr_fd.c\
	ft_putstr_fd.c\
	ft_split.c\
	ft_itoa.c\
	ft_itoa_unsigned.c\
	ft_strmapi.c\
	ft_memdel.c\
	ft_lstnew.c\
	ft_lstadd_front.c\
	ft_lstsize.c\
	ft_lstlast.c\
	ft_lstadd_back.c\
	ft_lstdelone.c\
	ft_lstclear.c\
	ft_lstiter.c\
	ft_lstmap.c\
	ft_exit.c\
	ft_itoa_base.c\
	ft_itoa_address.c\
	ft_str_toupper.c\
	ft_str_tolower.c\
	ft_ptr_lst.c
PRINTF_DIR = ft_printf
PRINTF = ft_printf.c\
			pf_arg.c\
			pf_fill_1_5.c\
			pf_fill_6_9.c\
			pf_parsing.c\
			pf_precision.c\
			pf_width.c\
			ft_printf_e.c\
			pf_fill_1_5_e.c\
			pf_fill_6_9_e.c
PRINTF_SRCS = $(addprefix $(PRINTF_DIR)/, $(PRINTF))

OBJS = $(addprefix $(OBJSDIR)/, $(SRCS:.c=.o))
PRINTF_OBJS = $(addprefix $(OBJSDIR)/, $(PRINTF_SRCS:.c=.o))

DPDCS = $(OBJS:.o=.d)

INCLUDES = -I ./libft.h
CFLAGS = -Wall -Wextra -Werror
LOGFILE = $(LOGPATH) `date +'%y.%m.%d %H:%M:%S'`
MSG = ---

all : $(NAME)

opti :
	@(make -j all)

-include $(DPDCS)

$(NAME) : $(OBJS) $(PRINTF_OBJS)
	@(ar rcs $(NAME) $(OBJS) $(PRINTF_OBJS))
	@(echo "Libft created")

$(OBJSDIR)/%.o : %.c | $(OBJSDIR)
	@(echo "Compiling -> $^")
	@(clang $(CFLAGS) -MMD -c $< -o $@)

$(OBJSDIR) :
	@(mkdir -p .objs)
	@(mkdir -p .objs/ft_printf)

clean :
	@(rm -f $(NAME))
	@(echo "Libft deleted")

fclean : clean
	@(rm -rf $(OBJSDIR))
	@(echo "Objects and dependences deleted")

git : fclean
	@(git add *)
	@(git commit -m "$(LOGFILE) : $(MSG)")
	@(git push)

re : fclean all
