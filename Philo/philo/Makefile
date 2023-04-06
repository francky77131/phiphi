# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: frgojard <frgojard@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/28 14:56:02 by frgojard          #+#    #+#              #
#    Updated: 2023/03/28 14:56:04 by frgojard         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

SRCS =	main.c \
		philo_parsing.c \
		philo_th.c \
		philo_utils.c \
		philo_free.c

OBJS = $(SRCS:.c=.o)

CC = cc
CFLAGS = -g3 -Wall -Wextra -Werror -pthread


all: ${NAME}

${NAME}: ${OBJS}
	${CC} ${CFLAGS} ${OBJS} -o ${NAME}

clean:
	rm -f ${OBJS}

fclean: clean
	rm -f ${NAME}

re: fclean all

.PHONY: all clean fclean re