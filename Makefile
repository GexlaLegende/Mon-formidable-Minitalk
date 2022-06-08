# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: apercebo <apercebo@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/01/19 12:15:08 by apercebo          #+#    #+#              #
#    Updated: 2022/03/24 18:26:49 by apercebo         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= libftminitalk

CC		= gcc
RM		= rm -f
SERVER	= server
CLIENT	= client
PRINTF	= printf
SOURCES1 = client.c
SOURCES2 = server.c
OBJS1 = $(SOURCES1:.c=.o)
OBJS2 = $(SOURCES2:.c=.o)

CFLAGS	= -Wall -Wextra -Werror

all:		${NAME}

${NAME}:	${SERVER} ${CLIENT}

%.o:	%.c
	${CC} ${CFLAGS} -c $< -o $@

###############################--SERVER--###############################

${SERVER}:	${OBJS2} Makefile
			make -C ./ft_printf
			${CC} ${CFLAGS} ./ft_printf/libftprintf.a server.o -o ${SERVER}

###############################--CLIENT--###############################

${CLIENT}:	${OBJS1}
			${CC} ${CFLAGS} $< -o ${CLIENT}

###############################--RESTE--################################

clean:
			${RM} server.o
			${RM} client.o
			make clean -C ./ft_printf

fclean:		clean
			make fclean -C ./ft_printf
			${RM} server
			${RM} client

re:			fclean all

${PRINTF}:		
		@make -C ./ft_printf

.PHONY:		all clean fclean re