# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: heom <heom@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/07/02 12:36:58 by hekang            #+#    #+#              #
#    Updated: 2021/08/31 17:41:43 by heom             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= minishell

GCCFLAG = -Wall -Werror -Wextra
RM 		= rm -f

SRCS	= main env cmd ft_chdir ft_echo ft_pwd all ft_export ft_unset validate_env_key ft_print_endcode\
		err_msg parse_utility cmdline_split cmdline_split_util parser ft_exit signal parse_utility2\
		handle_redirection check_env_key validate_redirect_expression conv_env_var init_signal init_pipefd_backup\
		handle_input is_builtin handle_parsed_data handle_pipe pipe_utils parse_quote_str divide_redirection \
		str_extension
LIBFT	= ft_split ft_strncmp ft_strjoin ft_strlen ft_memcpy ft_calloc ft_memset ft_strlcpy ft_lstnew ft_lstadd_back\
		ft_lstlast ft_putendl_fd ft_lstsize ft_strdup ft_isalpha ft_isdigit ft_putnbr_fd ft_putchar_fd ft_putstr_fd\
		ft_isspace ft_substr ft_isprint ft_strchr ft_bzero ft_atoi ft_strnstr ft_itoa
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
		gcc $(GCCFLAG) $^ -o $@ $(LIBS) -g -fsanitize=address

clean : 
		$(RM) $(OBJS)

fclean : clean
		$(RM) $(NAME)

re :	fclean all

.PHONY: all clean fclean re