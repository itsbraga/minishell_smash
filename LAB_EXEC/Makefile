# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pmateo <pmateo@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/03/20 14:22:48 by pmateo            #+#    #+#              #
#    Updated: 2024/09/14 18:15:34 by pmateo           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
FLAGS = -Werror -Wextra -Wall -g -g3
RM = rm -f
.DEFAULT_GOAL := all

NAME = mini_exec

DIR_LIBFT = ../LIBFT
LIBFT = 	${DIR_LIBFT}/libft.a

DIRINC_LIBFT = 		${DIR_LIBFT}/INCLUDES
DIRINC_MINIEXEC = ./INCLUDES
INCFILES = 			${DIRINC_MINIEXEC}/mini_exec.h

DIR_SRCS = 			./SRCS/
SRCS = 				main.c init.c token_utils.c \
					EXEC/exec.c EXEC/pathfinder.c

OBJ = ${SRCS:.c=.o}

OBJ_INIT = ${SRCS/INIT:.c=.o}

%.o: ${DIR_SRCS}%.c ${INCFILES}
	${CC} ${FLAGS} -c $< -o $@ -I ${DIRINC_MINIEXEC} -I ${DIR_LIBFT}

%.o: ${DIR_SRCS}INIT/%.c ${INCFILES}
	${CC} ${FLAGS} -c $< -o $@ -I ${DIRINC_MINIEXEC} -I ${DIR_LIBFT}

${LIBFT}:
	${MAKE} -s -C ${DIR_LIBFT}

${NAME}: ${OBJ} ${OBJ_INIT} ${LIBFT} ${INCFILES}
	${CC} ${FLAGS} -o ${NAME} ${OBJ} ${OBJ_INIT} -I ${DIRINC_MINIEXEC} -I ${DIRINC_LIBFT} -L ${DIR_LIBFT} -lft -lreadline

all: ${LIBFT} ${NAME}
		@echo "\033[1;5;32m# MINI_EXEC READY ! #\033[0m"

clean:
		@${MAKE} -s -C ${DIR_LIBFT} clean
		@${RM} ${OBJ} ${OBJ_BONUS}
		@echo "\033[1;9;35m# No more object files. #\033[0m"

fclean: clean
		@${MAKE} -s -C ${DIR_LIBFT} fclean
		@${RM} ${NAME} ${NAME_BONUS}
		@echo "\033[1;9;35m# No more executable files. #\033[0m"

re: fclean all

.PHONY: all re clean fclean