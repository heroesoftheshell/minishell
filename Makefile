# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hekang <hekang@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/07/02 12:36:58 by hekang            #+#    #+#              #
#    Updated: 2021/07/27 22:42:55 by hekang           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= minishell

GCCFLAG = -Wall -Werror -Wextra
RM 		= rm -f

SRCS	= main env cmd ft_chdir ft_echo ft_pwd 
LIBFT	= ft_split ft_strncmp ft_strjoin ft_strlen ft_memcpy ft_calloc ft_memset ft_strlcpy
# SRCS		= parse_test.c err_msg.c env.c

OBJS	= $(FIL:.c=.o)
INCS	= -I./includes
LIBS	= -L./lib -lreadline -ltermcap -lhistory

FIL		= \
		$(addsuffix .c, $(addprefix srcs/, $(SRCS))) \
		$(addsuffix .c, $(addprefix libft/, $(LIBFT))) 

all :	$(NAME)

$(OBJS): %.o : %.c includes/minishell.h includes/libft.h
		gcc $(GCCFLAG) $(INCS) -c -o $@ $<

# srcs/main.o : srcs/main.c
# 		gcc $(GCCFLAG) $(INCS) -c -o $@ $<

$(NAME) : $(OBJS)
		gcc $(GCCFLAG) $^ -o $@ $(LIBS)

clean : 
		$(RM) $(OBJS)

fclean : clean
		$(RM) $(NAME)

re :	fclean all

.PHONY: all clean fclean re