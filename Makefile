# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hekang <hekang@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/07/02 12:36:58 by hekang            #+#    #+#              #
#    Updated: 2021/07/06 12:42:18 by hekang           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC		= main.c

SRCDIR	= ./srcs/
SRCS 	= $(addprefix $(SRCDIR), $(SRC))

OBJS	= $(SRCS:.c=.o)

INCDIR	= ./includes/
LIBDIR	= ./libft/
LIBNAME = libft.a

NAME	= minishell

GCC 	= GCC
GCCFLAG = -Wall -Werror -Wextra
# -g -fsanitize=address
RM 		= rm -f

%.o:		%.c
		$(GCC) $(GCCFLAG) -I$(INCDIR) -c $< -o $@

all:		$(NAME)

$(NAME):	$(LIBNAME) $(OBJS)
		$(GCC) $(GCCFLAG) -I$(INCDIR) -o $(NAME) $(OBJS) -lreadline $(LIBNAME)

bonus:		all

$(LIBNAME):
		@$(MAKE) -C $(LIBDIR) bonus
		@cp $(addprefix $(LIBDIR), $(LIBNAME)) $(LIBNAME)

clean:
		$(RM) $(OBJS) $(OJBS_B)

fclean:		clean
		$(RM) $(NAME) $(LIBNAME)
		@$(MAKE) -C $(LIBDIR) fclean

re:			fclean all

.PHONY:		all clean fclean re bonus
