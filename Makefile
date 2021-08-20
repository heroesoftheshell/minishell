# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hekang <hekang@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/07/02 12:36:58 by hekang            #+#    #+#              #
#    Updated: 2021/08/20 10:44:21 by hekang           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= minishell

GCCFLAG = -Wall -Werror -Wextra
RM 		= rm -f

SRCS	= main env cmd ft_chdir ft_echo ft_pwd all ft_export ft_unset
LIBFT	= ft_split ft_strncmp ft_strjoin ft_strlen ft_memcpy ft_calloc ft_memset ft_strlcpy ft_lstnew ft_lstadd_back\
		ft_lstlast ft_putendl_fd ft_lstsize ft_strdup ft_isalpha ft_isdigit
# SRCS	= parse_test err_msg env parse_utility cmdline_split cmdline_split_util
# LIBFT	= ft_split ft_strncmp ft_strjoin ft_strlen ft_memcpy ft_calloc ft_memset\
			ft_strlcpy ft_isspace ft_substr ft_putchar_fd ft_putstr_fd ft_putendl_fd\
			ft_isprint ft_strchr ft_bzero


OBJS	= $(FIL:.c=.o)
INCS	= -I./includes
UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S),Linux)
	LIBS =  -L./lib/linux -lreadline -ltermcap -lhistory
else
	LIBS =  -L./lib -lreadline -ltermcap -lhistory
endif

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