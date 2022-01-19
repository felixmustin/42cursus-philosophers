# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fmustin <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/01/18 16:47:19 by fmustin           #+#    #+#              #
#    Updated: 2022/01/18 16:47:20 by fmustin          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS		=	srcs/main.c \
				srcs/philo.c \
				srcs/init.c \
				srcs/utils.c \
				srcs/actions.c \

INCLUDES	=	includes/main.h

OBJS 		=	$(SRCS:.c=.o)

NAME		=	philo

CC			=	gcc

CCFLAGS		=	-Wall -Wextra -Werror

%.o: %.c
			$(CC) $(CCFLAGS) -I ${INCLUDES} -c $<  -o $(<:.c=.o)

all:		${NAME}

${NAME}:	${OBJS} ${INCLUDES}
				$(CC) $(CCFLAGS) -lpthread -o $(NAME) $(OBJS)

clean:
				rm -f ${OBJS}

fclean: 	clean
				rm -f ${NAME}

re:				fclean all

.PHONY:			all clean fclean re
